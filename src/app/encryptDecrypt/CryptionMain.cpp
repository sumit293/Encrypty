#include <iostream>
#include "CryptionMain.hpp"

int main(int argc  , char *argv[]) {
   if(argc !=2){
    std::cout<<"Usage:./CryptionMain <taskData>"<<std::endl;
    return 1;

   }
   executeCryption(argv[1]);

    return 0;
}