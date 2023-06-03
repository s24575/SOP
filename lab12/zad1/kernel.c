#define SCREEN_WIDTH 80

unsigned short* screen = (unsigned short*)0xB8000;

void write_char(char character, unsigned char color) {
    *screen++ = (color << 8) | character;
}

void write_string(const char* str){
   for(int i = 0; str[i] != '\0'; i++){
      write_char(str[i], 0x0F);
   }
}

__asm__ (".pushsection .text.start\r\n" \
   "jmp main\r\n" \
   ".popsection\r\n"
);


int main(){
   write_string("My first OS has been loaded!");

   while(1);
   return 0;
}