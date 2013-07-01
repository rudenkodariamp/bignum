#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bignumc.h"
// поиск максимального
int max(int a, int b) {
    return (a > b ? a : b);
}
// чтение из файла
bignum bigread(const char *s) {
    bignum res;
    int i;
    FILE *fp = fopen(s, "r+");
	if (fp == NULL) {
		printf("file open err\n");
		exit(1);
	}
	
	char sign;
	fread(&sign, 1, 1, fp);
    int signoff = 0;
    if (sign == '-') 
        signoff = 1;
	//file size
	fseek(fp, -1L, SEEK_END);
    int size = ftell(fp) - signoff;
    if (isdigit(getc(fp))) {
        size++;
    }
    res = allocmem(size);
	res.sign = signoff;
    fseek(fp, signoff, SEEK_SET);
    for (i = size - 1; i >= 0; i--) {
        char c;
        c = getc(fp);
        res.d[i] = c - '0';        
    }
    for (i = size - 1; i>=0; --i) {
        if (res.d[i] != 0)
            break;
        res.size--;
    }
    fclose(fp);
    return res;
}
// копирование числа
bignum bigcopy(bignum obj) {
    bignum res = allocmem(obj.size);
    res.sign=obj.sign;
    int i;
    for (i = 0; i<res.size; ++i)
        res.d[i] = obj.d[i];
    return res;
}
// выделение памяти
bignum allocmem(int size) {
	bignum res;
	res.sign = 0;
	res.size = size;
	res.d = calloc(size, 1); 
	if (res.d == NULL) {
		printf("alloc err\n");
		exit(1);
	}
	return res;
}
// вывод на экран
void bigout(bignum res) {
    if (res.sign)
        printf("-");
    int i;
    for (i = res.size - 1; i >= 0; i--)
        printf("%d", res.d[i]);
    printf("\n");
}
// вывод в файл
void bigwrite(bignum res, const char *f) {
    FILE *fp = fopen(f, "w+");
    if (fp == NULL) {
        printf("write to file err\n");
        exit(1);
    }
    if (res.size == 0) {
        fprintf(fp, "0");
    } else {
        if (res.sign)
            fprintf(fp, "-");
        int i;
        for (i = res.size - 1; i >= 0; i--)
            fprintf(fp, "%d", res.d[i]);
    }
    fclose(fp);
}
// очищение памяти
void freemem(bignum res) {
    free(res.d);
}

// сравнитель чисел
int bigcompare(bignum a1, bignum a2) {
    int i, k1 = (a1.sign ? -1 : 1), k2 = ( a2.sign ? 1 : -1);
    /*
    a1>a2 return 1
    a1<a2 return -1
    a1=a2 return 0
    */
    if (a1.sign&&!a2.sign) return -1;
    if (!a1.sign&&a2.sign) return 1;
    if (a1.size<a2.size) return -1;
    if (a1.size>a2.size) return 1;
    for (i=a1.size;i>=0;--i) {
            if (a1.d[i]>a2.d[i]) return k1;
            if (a1.d[i]<a2.d[i]) return k2;
    }
    return 0;
}
// вычитание знаковое
bignum bigsubz(bignum a1, bignum a2) {
    bignum res;
    //a>0 b<0 = a+b
    if (!a1.sign&&a2.sign) {
        res = bigaddbz(a1,a2);        
    }
    //a<0 b>0 = -(|a|+|b|)
    if (a1.sign&&!a2.sign) {
        res = bigaddbz(a1,a2);        
        res.sign=1-res.sign;
    }
    //a<0 b<0 =  |b|-|a| 
    if (a1.sign&&a2.sign) {
        res =bigsubbz(a2,a1);
        res.sign = 1 - res.sign;
    }
    if (!a1.sign && !a2.sign) {
        res = bigsubbz(a1,a2);    
    }
    return res;
} 
//вычитание беззнаковое
bignum bigsubbz(bignum a1, bignum a2) {
    bignum res = allocmem(max(a1.size, a2.size));
    if (bigcompare(a1, a2) == -1) {
        bignum tmp = a1;
        a1 = a2;
        a2 = tmp;        
        res.sign = 1;
    }
    int i,c=0;
    for (i=0;i<a1.size;++i) {
        c+=a1.d[i]-a2.d[i]+10;
        res.d[i]=c%10;
        if (c<10) c=-1; else c=0;
    }
    while (res.d[res.size - 1]==0&&res.size>=1) res.size--;
    return res;
}

// сложение знаковое
bignum bigaddz(bignum a1, bignum a2) {
    bignum res;
    //a>0 b<0 = |a|-|b| 
    if (!a1.sign&&a2.sign) {
        res = bigsubbz(a1,a2);       
    }
    //a<0 b>0 = |b|-|a|
    if (a1.sign&&!a2.sign) {
        res = bigsubbz(a2,a1);        
    }
    //a<0 b<0 = -(|a|+|b|) 
    if (a1.sign&&a2.sign) {
        res = bigaddbz(a1, a2);
        res.sign = 1;
    }
    if (!a1.sign && !a2.sign) {
        res = bigaddbz(a1,a2);    
    }
    return res;
}
//сложение беззнаковое
bignum bigaddbz(bignum a1, bignum a2) { 
    bignum res = allocmem(max(a1.size, a2.size)+1);
    int i,c=0,j,k,m=max(a1.size,a2.size); 
    for (i=0;i<m;++i) {
	j=a1.d[i];
	k=a2.d[i];
	if (i > a1.size) j = 0;
	if (i > a2.size) k = 0;
        c+=j+k;
        res.d[i]=c%10;
        c/=10;
    }
    if (c>0) {
	m=m+1;
        res.d[m]=c;
   }
    res.size=m;
    if ((res.d[m-1] == 0) && (m>1)) res.d[m-1] = 1;
    return res;
}
//умножение
bignum bigmul(bignum a1,bignum a2) {
    bignum res = allocmem(a1.size + a2.size);
    res.size = 0;
    int c=0,i,j,k;
    if ((a1.sign&&a2.sign)||(!a1.sign&&!a2.sign)) res.sign=0; else res.sign=1;
    for (i=0;i<a1.size;++i) 
        for (j=0;j<a2.size;++j) {
        k=i+j;
        c=a1.d[i]*a2.d[j];
        while (c) {
            c+=res.d[k];
            res.d[k]=c%10;
            c/=10;
            if (k+1>res.size) 
                res.size=k+1;
            k++;                
        }
    } 
    return res;
}
// умножение большого числа на инт
bignum bigmultoint(bignum a1, int a2) {
    if (a2 == 0) {
        bignum zero = allocmem(0);
        return zero;
    }
    bignum res = allocmem(a1.size + (int)log10(a2) + 1);
    int a2sign = a2 < 0;
    if (a2 < 0) {
        a2 = -a2;
    }
    res.size = a1.size;
    int c=0,i,j,k;
    if ((a1.sign&&a2sign)||(!a1.sign&&!a2sign)) 
        res.sign=0; 
    else 
        res.sign=1; 
    long long r = 0;
    for (i=0;i<res.size|r;i++) {
        long long tmp = a2;
        if (i < a1.size)
            tmp *= a1.d[i];
        else
            tmp = 0;
        tmp += r;
        res.d[i] = tmp%10;
        r = tmp / 10;
   
        if (res.d[res.size])
            res.size++;
    }

    return res;
}

//деление
bignum bigdiv(bignum a1, bignum a2)
{
    if (a2.size == 0)
        exit(1);
    if (bigcompare(a1,a2) < 0) {
        bignum zero=allocmem(0);
        return zero;
    }
    bignum res = allocmem(a1.size-a2.size+1);
    if ((a1.sign&&a2.sign)||(!a1.sign&&!a2.sign)) res.sign=0; else res.sign=1;
    bignum curvalue  = allocmem(a2.size + 1);
    a2.sign = a1.sign = 0;
    curvalue.size = 1;
    int i;  
    for (i = a1.size-1; i>=0; i--)  {
        int j; 
        if (curvalue.size > 0) {
            for (j = curvalue.size;j>=1;j--)
                curvalue.d[j] = curvalue.d[j-1];
            if (curvalue.d[curvalue.size])
                curvalue.size++;
        } else
            curvalue.size = 1;
        curvalue.d[0] = a1.d[i];
        int x = 0;
        int l = 0, r = 10;
        while (l <= r) {
            int m = (l + r) >> 1;
            bignum cur = bigmultoint(a2, m);
            if (bigcompare(cur, curvalue) <= 0)  {
                x = m;
                l = m+1;
            } else
                r = m-1;
        }
        res.d[i] = x;
        bignum tmp = bigmultoint(a2, x),
            tmp2 = bigsubbz(curvalue, tmp);
        freemem(curvalue);
        curvalue = tmp2;
        freemem(tmp);
    }

    int pos = a1.size;
    while (pos>=0 && !res.d[pos])
        pos--;
    res.size = pos+1;
    freemem(curvalue);
    return res;
}


// модуль
bignum bigmod(bignum a1, bignum a2) {
    if (a2.size == 0)
        exit(1);
    if (!a1.sign && !a2.sign)
        if (bigcompare(a1,a2) < 0) {
            bignum re=bigcopy(a1);
            return re;
        }
    int a1sign=a1.sign, a2sign=a2.sign;

    bignum curvalue  = allocmem(a2.size + 1);
    a2.sign = a1.sign = 0;
    curvalue.size = 1;
    int i;  
    for (i = a1.size-1; i>=0; i--)  {
        int j; 
        if (curvalue.size > 0) {
            for (j = curvalue.size;j>=1;j--)
                curvalue.d[j] = curvalue.d[j-1];
            if (curvalue.d[curvalue.size])
                curvalue.size++;
        } else
            curvalue.size = 1;
        curvalue.d[0] = a1.d[i];
        int x = 0;
        int l = 0, r = 10;
        while (l <= r) {
            int m = (l + r) >> 1;
            bignum cur = bigmultoint(a2, m);
            if (bigcompare(cur, curvalue) <= 0)  {
                x = m;
                l = m+1;
            } else
                r = m-1;
        }
        bignum tmp = bigmultoint(a2, x),
            tmp2 = bigsubbz(curvalue, tmp);
        freemem(curvalue);
        curvalue = tmp2;
        freemem(tmp);
    }
    for (i = curvalue.size-1; i>=0; --i) {
        if (curvalue.d[i] != 0)
            break;
        curvalue.size--;
    }
	if (curvalue.size != 0 && a1sign ^ a2sign) {
		bignum old = curvalue;
		curvalue = bigsubbz(a2, curvalue);
		freemem(old);
	}

	curvalue.sign = a2sign;

    return curvalue;
}
// смена знака
bignum bigneg(bignum a) {
    a.sign = !a.sign;
    return a;
}
