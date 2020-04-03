int fibbonacci(int a, int b) {
   if(a == 0){
      return 1;
   } else {
      return (b+fibbonacci(a-1, b));
   }
}