int clamp(int x,int min,int max){
    if(x > max) return max;
    if(x < min) return min;
    return x;
}