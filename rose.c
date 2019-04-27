
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
#include <stdio.h>
#define PATH_MAX 2500
#if defined(__linux__) //linux
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__) 
#define MYOS 4  // freebsd
#define PATH_MAX 2500
#else
#define MYOS 0
#endif
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <time.h>


#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>

int tex_item_level = 0;



/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}


void ncp( char *targetfile, char *sourcefile )
{
   FILE *source, *target; 
   int ch ; 
   source = fopen( sourcefile , "r");
   if( source == NULL )
   {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   target = fopen( targetfile , "w");
   if( target == NULL )
   {
      fclose(source);
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   printf("  >Source: %s\n",  sourcefile );
   printf("  >Target: %s\n",  targetfile );
   printf("  >Copying...\n");

   while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
 
   printf("File copied successfully.\n");
   fclose(source);
   fclose(target);
}




/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
char *strcol( char *str , int leftchar , int rightchar )
{  
      char ptr[strlen(str)+1];
      //int myitem = myitemfoo +1;
      int i,j=0;
      int fooitem = 0;
      int inside = 0; 
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == rightchar ) 
          inside = 0;

        if ( str[i] == leftchar ) 
          inside = 1;
        else
         if ( inside == 1 ) 
         //if ( str[i] == mychar ) 
          // fooitem++;
            ptr[j++]=str[i];



        //else if ( str[i] != mychar &&  fooitem == myitem-2  ) 
        //   ptr[j++]=str[i];

      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}




char *strcut( char *str , int myposstart, int myposend )
{  
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}






char *fbasenoext(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}


///////////////////////////////////////////
void readfile( char *filesource )
{
   FILE *source; 
   int ch ; 
   source = fopen( filesource , "r");
   while( ( ch = fgetc(source) ) != EOF )
   {
         printf( "%c", ch );
   }
   fclose(source);
}




///////////////////////////////////////////
void readfileline( char *fileoutput , char *filesource )
{
   FILE *source; 
   FILE *target; 
   FILE *fp5; 
   int ch, c, co;
   char lline[PATH_MAX];
   char ncpfile[PATH_MAX];
   char charo[PATH_MAX];
   int pcc = 0;
   int linecount = 0;
   int posx    = 100;
   int posy    = 730;
   int posxmax = 588;
   int posymax = 835;

   source = fopen( filesource , "r");
   target = fopen( fileoutput , "wb+");

   int export_skip = 0;
   int area_archive = 0;
   int fileeof = 0;
   while( fileeof == 0 )
   {
       export_skip = 0;
       c = fgetc(source); 
       if ( c == EOF ) fileeof = 1;

       else
       {
           if ( c != '\n' )
               lline[pcc++]=c;


           if ( ( lline[ 0 ] == '!' )  && ( lline[ 1 ] == 'E' ) && ( lline[ 2 ] == 'O' )  && ( lline[ 3 ] == 'F' )  )
              fileeof = 1;


           if ( ( lline[ 0 ] == '/' )  && ( lline[ 1 ] == '*' ) ) 
               area_archive = 1;

           if ( ( lline[ 0 ] == '*' )  && ( lline[ 1 ] == '/' ) ) 
           {    area_archive = 0;  export_skip = 1;       }


           if ( fileeof == 0 )
           if ( c == '\n' ) 
           {
             lline[pcc++]='\0';

             printf( "%s", lline );
             printf( "\n" );

             if ( area_archive == 0 )
             {
              if ( export_skip == 0 )
              {
               // REM
               if (  ( lline[ 0 ] == '/' ) && ( lline[ 1 ] == '/' )  )
               {
                   printf( "Rem : do nothing.\n" );
               }


               ////////////////////////////
               // item header
               ////////////////////////////
               else if (  ( lline[ 0 ] == '!' ) && ( lline[ 1 ] == '>' ) &&  ( lline[ 2 ] == ' ' ) )
               {
                 if ( tex_item_level == 0  )
                 {
                    tex_item_level = 1;
                    fputs( "\\begin{itemize}\n" , target);
                 }
                 fputs( "\\item " , target);
                 fputs( strcut( lline, 2 +2 , strlen( lline )) , target);
                 fputs( "\n" , target);
               }






               ////////
               ////////////////////////////
               // !latex 
               ////////
               else if ( ( lline[ 0 ] == '!' ) && ( lline[ 1 ] == 'l' ) &&  ( lline[ 2 ] == 'a' ) 
                  && ( lline[ 3 ] == 't' ) && ( lline[ 4 ] == 'e' ) &&  ( lline[ 5 ] == 'x' )  )
               {
                 fputs( "\n" , target);
                 fputs( "\\documentclass[a4paper,11pt]{article}\n" , target);
                 fputs( "\\usepackage{graphicx}\n" , target);
                 fputs( "\n" , target);
               }



               ////////////////////////////
               // !tex 
               ////////
               ////////
               else if (  ( lline[ 0 ] == '!' ) && ( lline[ 1 ] == 't' ) &&  ( lline[ 2 ] == 'e' ) && ( strstr( lline, "!tex" ) != 0 ) )
               {
                 fputs( "\n" , target);
                 fputs( "\\documentclass[a4paper,11pt]{article}\n" , target);
                 fputs( "\n" , target);
               }

               ////////////////////////////
               // !begin 
               ////////
               ////////
               else if (  ( lline[ 0 ] == '!' ) && ( lline[ 1 ] == 'b' ) &&  ( lline[ 2 ] == 'e' ) 
                  && ( strstr( lline, "!begin" ) != 0 ) )
               {
                 fputs( "\n" , target);
                 fputs( "\\begin{document}\n" , target);
                 fputs( "\n" , target);
               }

               ////////////////////////////
               // !line 
               ////////////////////////////
               else if (  ( lline[ 0 ] == '!' ) 
               &&  ( lline[ 1 ] == 'l' ) 
               &&  ( lline[ 2 ] == 'i' ) 
               &&  ( lline[ 3 ] == 'n' ) 
               &&  ( lline[ 4 ] == 'e' ) 
               &&  ( lline[ 5 ] == ' ' ) 
               )
               {
                 fputs( strcut( lline, 5 +2 , strlen( lline )) , target);
                 fputs( "\\" , target);
                 fputs( "\\" , target);
                 fputs( "\n" , target);
               }



               ////////////////////////////
               // !clr 
               else if (  ( lline[ 0 ] == '!' ) 
               &&  ( lline[ 1 ] == 'c' ) 
               &&  ( lline[ 2 ] == 'l' ) 
               &&  ( lline[ 3 ] == 'r' ) 
               )
               {
                 fputs( "\\clearpage\n" , target);
                 fputs( "\n" , target);
               }

               ////////////////////////////
               // !nullclr 
               else if (  ( lline[ 0 ] == '!' ) 
               &&  ( lline[ 1 ] == 'n' ) 
               &&  ( lline[ 2 ] == 'u' ) 
               &&  ( lline[ 3 ] == 'l' ) 
               &&  ( lline[ 4 ] == 'l' ) 
               &&  ( lline[ 5 ] == 'c' ) 
               &&  ( lline[ 6 ] == 'l' ) 
               &&  ( lline[ 7 ] == 'r' ) 
               )
               {
               }

               ////////////////////////////
               // !maths 
               else if (  ( lline[ 0 ] == '!' ) 
               &&  ( lline[ 1 ] == 'm' ) 
               &&  ( lline[ 2 ] == 'a' ) 
               &&  ( lline[ 3 ] == 't' ) 
               &&  ( lline[ 4 ] == 'h' ) 
               &&  ( lline[ 5 ] == 's' ) 
               )
               {
                 fputs( "\\usepackage{amsmath}\n" , target);
                 fputs( "\\usepackage{graphicx}\n" , target);
                 fputs( "\\usepackage{epstopdf}\n" , target);
                 fputs( "\n" , target);
               }

               // !box  
               else if (  ( lline[ 0 ] == '!' ) 
               &&  ( lline[ 1 ] == 'b' ) 
               &&  ( lline[ 2 ] == 'o' ) 
               &&  ( lline[ 3 ] == 'x' ) 
               &&  ( lline[ 4 ] == ' ' ) 
               )
               {
  	         fputs( "\\begin{center}", target );
  	         fputs( "\\boxed{", target );
 	         fputs(  strcut( lline, 4+2, strlen( lline )) , target );
  	         fputs( "}", target );
  	         fputs( "\\end{center}", target );
  	         fputs( "\n", target );
               }


              else if (  ( lline[ 0 ] == '!' ) 
              &&  ( lline[ 1 ] == 'i' ) 
              &&  ( lline[ 2 ] == 'm' ) 
              &&  ( lline[ 3 ] == 'g' ) 
              &&  ( lline[ 4 ] == '[' ) 
              )
              {
  	        fputs( "\\begin{center}\n", target );
  	        fputs( "\\includegraphics[scale,height=" , target );
 	        fputs( strcol( lline,  '[' ,']' ) , target );
                fputs( "\\textheight]{" , target );
 	        fputs( strcol( lline,  '{' ,'}' ) , target );
  	        fputs( "}\n", target );
  	        fputs( "\\end{center}\n", target );
               }



               ////////////////////////////
               // !fig 
               else if (  ( lline[ 0 ] == '!' ) 
               &&  ( lline[ 1 ] == 'f' ) 
               &&  ( lline[ 2 ] == 'i' ) 
               &&  ( lline[ 3 ] == 'g' ) 
               &&  ( lline[ 4 ] == ' ' ) 
               )
               {
 	         fputs( "\\includegraphics[width=1.0\\textwidth,keepaspectratio]{" , target );
                 fputs( strcut( lline, 4 +2 , strlen( lline )) , target);
                 fputs( "}\n" , target);
               }


               ////////////////////////////
               // !img 
               else if (  ( lline[ 0 ] == '!' ) 
               &&  ( lline[ 1 ] == 'i' ) 
               &&  ( lline[ 2 ] == 'm' ) 
               &&  ( lline[ 3 ] == 'g' ) 
               &&  ( lline[ 4 ] == ' ' ) 
               )
               {
                 fputs( "\\includegraphics{" , target);
                 fputs( strcut( lline, 4 +2 , strlen( lline )) , target);
                 fputs( "}\n" , target);
               }


               else if ( ( lline[ 0 ] == '!' ) 
               &&  ( lline[ 1 ] == 'b' ) 
               &&  ( lline[ 2 ] == 'c' ) 
               &&  ( lline[ 3 ] == 'e' ) 
               &&  ( lline[ 4 ] == 'n' ) 
               &&  ( lline[ 5 ] == 't' ) 
               &&  ( lline[ 6 ] == 'e' ) 
               &&  ( lline[ 7 ] == 'r' ) 
               )
               {
                 fputs( "\\begin{center}\n" , target);
                 fputs( "\n" , target);
               }

               else if ( ( lline[ 0 ] == '!' ) 
               &&  ( lline[ 1 ] == 'e' ) 
               &&  ( lline[ 2 ] == 'c' ) 
               &&  ( lline[ 3 ] == 'e' ) 
               &&  ( lline[ 4 ] == 'n' ) 
               &&  ( lline[ 5 ] == 't' ) 
               &&  ( lline[ 6 ] == 'e' ) 
               &&  ( lline[ 7 ] == 'r' ) 
               )
               {
                 fputs( "\\end{center}\n" , target);
                 fputs( "\n" , target);
               }






               ////////////////////////////
               // !center 
               else if (  ( lline[ 0 ] == '!' ) 
               &&  ( lline[ 1 ] == 'c' ) 
               &&  ( lline[ 2 ] == 'e' ) 
               &&  ( lline[ 3 ] == 'n' ) 
               &&  ( lline[ 4 ] == 't' ) 
               &&  ( lline[ 5 ] == 'e' ) 
               &&  ( lline[ 6 ] == 'r' ) 
               &&  ( lline[ 7 ] == ' ' ) 
               )
               {
                 fputs( "\\begin{center}\n" , target);
                 fputs( strcut( lline, 7 +2 , strlen( lline )) , target);
                 fputs( "\n" , target);
                 fputs( "\\end{center}\n" , target);
               }


               ////////////////////////////
               // !section 
               else if (  ( lline[ 0 ] == '!' ) && ( lline[ 1 ] == 's' ) &&  ( lline[ 2 ] == 'e' ) 
               &&  ( lline[ 3 ] == 'c' ) && ( lline[ 4 ] == 't' ) &&  ( lline[ 5 ] == 'i' ) 
               &&  ( lline[ 6 ] == 'o' ) && ( lline[ 7 ] == 'n' ) &&  ( lline[ 8 ] == ' ' ) )
               {
                 fputs( "\n" ,  target);
                 fputs( "\\section{" , target);
                 fputs( strcut( lline, 8 +2 , strlen( lline )) , target);
                 fputs( "}\n" , target);
               }



               ////////////////////////////
               // !end 
               ////////
               else if (  ( lline[ 0 ] == '!' ) && ( lline[ 1 ] == 'e' ) &&  ( lline[ 2 ] == 'n' ) &&  ( lline[ 3 ] == 'd' )  )
               {
                 fileeof = 1;
                 fputs( "\n" , target);
                 fputs( "\\end{document}\n" , target);
                 fputs( "\n" , target);
               }


               else
               {
                 fputs( lline , target);
                 fputs( "\n" , target);
               }

              }
             }

             // clear
             lline[0]='\0';
             pcc = 0;

           }

           co = c; 
       }
   }
   fclose(source);
   fclose( target );
}











//////////////////////////////
void makepdf( char *thefile )
{
      char ftrg[PATH_MAX];
      char fscr[PATH_MAX];
      char mytargetfile[PATH_MAX];

      strncpy( ftrg, getenv( "HOME" ) , PATH_MAX );
      strncat( ftrg , "/" ,             PATH_MAX - strlen( ftrg ) - 1);
      strncat( ftrg , "doc.tex" ,       PATH_MAX - strlen( ftrg ) - 1);

      strncpy( mytargetfile, getenv( "HOME" ) , PATH_MAX );
      strncat( mytargetfile , "/" , PATH_MAX - strlen( mytargetfile ) - 1);
      strncat( mytargetfile , "doc.mrk" , PATH_MAX - strlen( mytargetfile ) - 1);

      if ( fexist( thefile ) == 1 )
      {
              strncpy( mytargetfile, getenv( "HOME" ) , PATH_MAX );
              strncat( mytargetfile , "/" , PATH_MAX - strlen( mytargetfile ) - 1);
              strncat( mytargetfile , "doc.mrk" , PATH_MAX - strlen( mytargetfile ) - 1);

              ncp( mytargetfile , thefile );

              strncpy( fscr, mytargetfile, PATH_MAX );
              readfileline( ftrg , fscr );

              system( " cd ; pdflatex   -shell-escape --interaction=nonstopmode doc.tex " );
              system( " cd ; export DISPLAY=:0 ;  mupdf doc.pdf " );
     }
}




///////////////////////////////////
///////////////////////////////////
///////////////////////////////////
int main( int argc, char *argv[])
{
    char fichier[PATH_MAX];
    char targetfile[PATH_MAX];
    char string[PATH_MAX];

    if ( argc == 2)
    if ( strcmp( argv[1] , "-str" ) ==  0 ) 
    {
       printf( "%s\n", strcol( "img[0.5]{brain",  '[',  ']'  ) );
       return 0;
    }

    if ( argc == 2)
    if ( strcmp( argv[1] , "time" ) ==  0 ) 
    {
       printf("%d\n", (int)time(NULL));
       return 0;
    }



    struct winsize w; // need ioctl and unistd 
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );
    printf("Env HOME:  %s\n", getenv( "HOME" ));
    printf("Env PATH:  %s\n", getcwd( string, PATH_MAX ) );
    printf("Env TERM ROW:  %d\n", w.ws_row );
    printf("Env TERM COL:  %d\n", w.ws_col );

    ///////////////
    if ( argc == 1)
    {
       printf("Usage: please enter a file to use this software." );
       printf("\n" );
       return 0;
    }

    ///////////////
    if ( argc == 2)
      strncpy( fichier, argv[ 1 ] , PATH_MAX );

    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if ( argc == 2)
    {
          strncpy( targetfile, fbasenoext( argv[ 1 ] ) , PATH_MAX );
          strncat( targetfile , ".tex" , PATH_MAX - strlen( targetfile ) -1 );
          printf( "> Target: %s\n" , targetfile );
          printf( "> Source: %s => Target: %s \n", argv[1] , targetfile  );
          printf( "\n" );
          printf( "\n" );
          readfileline( targetfile, argv[ 1 ] );
          printf( "\n" );
          printf( "\n" );
          printf( "Create PDF and display it...\n" );
          makepdf( targetfile );
          printf( "Bye.\n" );
    }
    return 0;
}


