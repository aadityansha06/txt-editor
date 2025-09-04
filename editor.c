





//
// https://viewsourcecode.org/snaptoken/kilo/index.html




#include<termios.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
   
    struct termios origi_termina_setting;// copy of originsl terminal setttng 






#define Ctrl_Key(arg) ((arg)& 0x1f) // arg takes argument like c,q, etc to make it
// ctr_c , ctrl_q ...
// & 0x1f represnts ctrl key 

void throwerror(const char *s){
    perror(s);
    exit(1);
}


void disablerawmode(){
        if (tcsetattr(STDIN_FILENO,TCSAFLUSH,&origi_termina_setting)==-1)
        {
            throwerror("tcsetattr");
        }
         
}
void enable_raw_mode(){
               if ( tcgetattr(STDIN_FILENO,&origi_termina_setting)==-1) // getting original terminal setting 
               {
                  throwerror("tcgetattr");
               }
              
 atexit(disablerawmode);

   struct termios raw = origi_termina_setting;
      

   // removing all the flags (i.e rules defiend by the terminal so that we can define our own rule )
     raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN ); // c_lfalge means local  flag
     // removing ctrl_v  IEXTEN
     // ICANon is used to remove canaon or cooked mode 
    // ISIG turn of Ctrl-C and Ctrl-z so that the programme don't terminte
    // BRKINT is part of some tradion as per the creator of kilo.c so idk 
    
    raw.c_iflag &= ~(IXON | BRKINT  | ICRNL | INPCK | ISTRIP );
    raw.c_oflag &= ~(OPOST); // to get new line terminal require (\r\n) , turining of this feature
    // for defining own \n and \r (\r means getting on the begging of every new line )

    // iflage means input flags 
    // IXON means to remove the ctrl-s and ctrl-q pause the tranmission of data from terminal to the user
    
                    //If you don’t set VMIN and VTIme , read() can hang forever until "enough" bytes arrive.
//      VMIN = minimum number of bytes read() should wait for before returning.

// VTIME = timeout (in tenths of a second, i.e. 1 = 0.1s).
raw.c_cc[VMIN]= 0;
raw.c_cc[VTIME]=1;// 01.sec or 100 milisecddd


     tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);



}

char read_editor_key();

void process_pressed_key(){
    char     c = read_editor_key();

  
   
    printf("%d('%c')\r\n",c,c);
   
    switch (c)
    {
    case Ctrl_Key('q'):
        exit(0);
        break;
    

       
    }
   

}
int main (){

    enable_raw_mode();


   while (1){
    read_editor_key();
   
     
   
    
    
   }

   
    return 0;
}



char read_editor_key(){
    static char  c;
    int read_return ; // it contain the value return by read 
    // sucess for 1 , no input -> 0 and for error -1
     while ( (read_return=  read(STDIN_FILENO,&c,1)!=1))
     {
        if (read_return==-1)throwerror("read");
        
      
        
     }
    
     return c;

}