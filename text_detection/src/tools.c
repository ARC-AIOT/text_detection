#include "tools.h"

uint32_t std(uint8_t *arr, uint8_t n) {
    uint8_t i;
    uint32_t avg = 0, out = 0;
    int32_t diff;
    for(i = 0; i < n; i++) {
        avg += *(arr+i);
    }
    avg = avg * 100 / n;
    for(i = 0; i < n; i++) {
        diff = (*(arr+i))*100-avg;
        out += (diff > 0)? diff : -1*diff;
    }
    return out/n;
}

uint32_t row_std(uint8_t *row, uint32_t len, uint8_t n) {
    uint8_t i;
    uint32_t sum = 0;
    for(i = 0; i < len/n; i++) {
        sum += std(&row[i*n], (i*n+n > len)? len-i*n : n);
    }
    return sum;
}

uint32_t mean(uint32_t *arr, uint32_t len) {
    uint32_t i, sum = 0;
    for(i = 0; i < len; i++) {
        sum += *(arr+i);
    }
    return sum/len;
}

void find_local_minimum(uint32_t *arr, uint32_t *idx, uint32_t len) {
    uint32_t avg = mean(&arr[0], len);
    uint32_t i, last = 0;
    int8_t cnt = 0, j;
    for(i = 1; i < len-1; i++) {
        if(arr[i] < avg && arr[i-1] > arr[i] && arr[i] < arr[i+1]) {
            for(j = cnt-1; j >= 0; j--) {
                if(idx[j]/1000 < i-last) {
                    idx[j+1] = idx[j];
                }
                else break;
            }
            idx[j+1] = (i-last)*1000+i;
            cnt = (cnt == 10)? 10 : cnt+1;
            last = i;
        }
    }
}