#include <iostream>
#include<fstream>
#include <string>
#include <cctype>
using namespace std;

//Sai Pranith Kasam, Sxk200161

//function for outputting contents of file to console
void printfile(fstream& ofile){
    //stores current position of pointer in variable
    long int pos = ofile.tellp();
    ofile.close();
    //opens file for input
    ofile.open("paint.txt", ios :: in);
    //checking if file opened properly
    if(!ofile.good()){
       cout << "could not open/read file" << endl;
       return;
    }
    //seeking to the beginning of the file
    ofile.seekg(0L);
    char temp;
    //reading in each char to temp and printing out to console
    while (!ofile.eof()){
        ofile.get(temp);
        cout << temp;
    }
    ofile.close();
    //opening file for input and output, to preserve contents
    ofile.open("paint.txt", ios :: in | ios :: out);
    if(!ofile.good()){
       cout << "could not open/read file" << endl;
       return;
    }
    //going back to stored position to continue rest of commands
    ofile.seekp(pos);
    //buffer lines
    cout << endl;
    cout << endl;
}

//function to draw East or West
void drawLeftRight(fstream& ofile, bool penstatus, bool bold,int num, char dir, bool print){
    //Bold is only valid if pen is down
    if(!penstatus && bold){
        return;
    }
    //checking if pen is down
   if (penstatus == true){
       //draw
      if (dir == 'E'){
          //draw to the right
           while(num > 0){
               //draw * or # depending on bold preference
               if (!bold && ofile.peek()!= '#'){
                ofile << '*';
               }
               else{
                ofile << '#';   
               }
               //decrease number
               num--;
           }
      }
      else{
            //draw to left 
         while(num > 0){
             //move pointer left two to accommodate for drawing the opposite direction
             ofile.seekp(-2L, ios :: cur);
             //draw * or # depending on bold boolean
             if(!bold && ofile.peek()!= '#'){
             ofile << '*';
             }
             else{
                ofile << '#'; 
             }
             //decrement number
             num--;
         }
     }
   }
   else{
       //move cursor
       if (dir == 'E'){
           //move cursor to the right
           while(num > 0){
               //move cursor to the right and decrease number
               ofile.seekp(1L, ios :: cur);
               num--;
           }
      }
      else{
        //move cursor to the left
         while(num > 0){
             //move cursor to the left and decrease number
             ofile.seekp(-1L, ios :: cur);
             num--;
         }
      }
   }
      if (print == true){
          //call function to print the file if print is true
          printfile(ofile);
      }
  }
  //function to draw north or south
void drawUpDown(fstream& ofile, bool penstatus, bool bold,int num, char dir, bool print){
    //Bold is only valid if pen is down
    if(!penstatus && bold){
        return;
    }
    //check pen status
    if (penstatus == true){
        //draw
      if (dir == 'S'){
            //draw down
           while(num > 0){
               //move down one row
               ofile.seekp(50L, ios :: cur);
               //draw * or # depending on bold preference
               if (!bold && ofile.peek()!= '#'){
               ofile << '*';
               }
               else{
                ofile << '#';   
               }
               //decrment number
               num--;
           }
      }
      else{
            //draw up
            while(num > 0){
                //move pointer to one row above
               ofile.seekp(-52L, ios :: cur);
               //draw a * or # depending on bold preference
               if (!bold && ofile.peek()!= '#'){
                ofile << '*';   
               }
               else{
                ofile << '#';   
               }
                //decrement number
               num--; 
            }  
      }
    }
    else{
        //move cursor
        if (dir == 'S'){
            //move cursor down
           while(num > 0){
               //move cursor down one row (51 bytes) and decrement counter
               ofile.seekp(51L, ios :: cur);
               num--;
           }
      }
      else{
          //move cursor up
            while(num > 0){
                //move cursor up a row (-51 bytes) and decrement counter
               ofile.seekp(-51L, ios :: cur);
               num--; 
            }  
      }
    }
     if (print == true){
         //call print function
         printfile(ofile);
  }
}
//function to skip line if command is invalid
void skipline(ifstream &ifile,char cur = 'l'){
    //if the current char is a newline char, we don't want to skip the bottom line
    char x = cur;
    //while it is not the end of the file and the char is not a newline, get the char
    while (!ifile.eof() && x != '\n'){
        ifile.get(x);
    }
    //pointer ends up at beginning of the next line
}


int main(){
  /////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////          DO  NOT CHANGE CODE BELOW THIS               //////////////
  /////////////////////////////////////////////////////////////////////////////////////////

  ifstream infile("paint_base.txt");
  ofstream outfile("paint.txt", ios::binary);
  string c;
  if (infile)
     while (getline(infile, c))
        outfile << c << "\n";

  infile.close();
  outfile.close();

  /////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////          DO  NOT CHANGE CODE ABOVE THIS               //////////////
  /////////////////////////////////////////////////////////////////////////////////////////
   char x;
   bool penstatus;
   char dir;
   int num;
   bool bold = false;
   bool print = false;
   long int boundcheck;
   //opening the output file 
   fstream ofile("paint.txt", ios :: binary | ios :: in | ios :: out);
   //checking if the output file opened properly
   if(!ofile.good()){
       cout << "could not open/read file" << endl;
       return 1;
   }
   ofile.seekp(1L);
   string inputname;
   cout << "Enter input file name: " << endl;
   cin >> inputname;
   //opening the input file from the user input
   ifstream ifile(inputname, ios :: binary);
   //checking if file opened properly
   if(!ifile.good()){
       cout << "could not open/read file" << endl;
       return 1;
   }
   //iterating throught the input file
   while(!ifile.eof()){
       //setting defaults for bold and print
        bold = false;
        print = false;
        //getting the first char
       ifile.get(x);
       //if it's a 1 or a 2, change the penstatus
       if (x == '1'){
           penstatus = false;
        }
       else if (x == '2'){
           penstatus = true;
        }
        //if it's neither, then it's an invalid command
        else{
            //skip to next line and start back at the beginning of the while loop
            skipline(ifile,x);
            continue;
        }
        //get next char
       ifile.get(x);
       //check if it is a comma, if not then skip to next line
       if (x != ','){
            skipline(ifile,x);
            continue;
       }
       //get the direction(next char)
       ifile.get(dir);
       //check if direction is valid
       if (dir != 'S' and dir != 'N' and dir != 'W' and dir != 'E'){
            skipline(ifile,dir);
            continue;
       }
        //get next comma
       ifile.get(x);
       if (x != ','){
            skipline(ifile,x);
            continue;
       }
       //get the distance of movement
      ifile >> num;
      // if the char is not a number, then it's an invalid command
      if(ifile.fail()){
          //reset the failbit
            ifile.clear();
            //get the invalid char and skip to next line
            ifile.get(x);
            skipline(ifile,x);
            //back to beginning of while loop
            continue;
      }
      //get current position of cursor in the output file
      boundcheck = ofile.tellp();
      if(dir == 'W'){
          //if the direction is west, calcualte the current column based on pointer location
          boundcheck = boundcheck%51;
          //if the column after the movement is less than zero, declare as out of bounds
          if(boundcheck - num <= 0){
                skipline(ifile);
                continue;
          }
      }
      if (dir == 'E'){
          //if direction is east, calculate current column
          boundcheck = boundcheck%51;
          //if column after movement is greater than 51, declare as out of bounds
          if(boundcheck + num > 51){
                skipline(ifile);
                continue;
          }
      }
      if(dir == 'N'){
          //if direction is north, calculate current row based on pointer position
          boundcheck = boundcheck/51;
          //if row after movement is less than zero, declare out of bounds
          if(boundcheck - num < 0){
            skipline(ifile);
            continue;
            } 
      }
      if(dir == 'S'){
          //if direction is south, calculate current row based on pointer position
          boundcheck = boundcheck/51;
          //if row after movement is less than zero, declare out of bounds
          if(boundcheck + num > 50){
            skipline(ifile);
            continue;
            }  
      }
      //if it is the end of the file(no next character), call drawing functions
      if(ifile.eof()){
          if (dir == 'E' || dir == 'W'){
            drawLeftRight(ofile, penstatus, bold, num, dir, print);
          }
          else{
              drawUpDown(ofile, penstatus, bold, num, dir, print);
          }
      }
      //get next char, validate if comma, newline, or invalid
       ifile.get(x);
      if (x == ','){
          ifile.get(x);
          //if comma, check if char after comma is B
          if (x == 'B'){
              //if char is B, set bold to true
              bold = true;
              ifile.get(x);
              if (x == ','){
                  //if comma after B, check if it's a P or invalid
                  ifile.get(x);
                  if(x == 'P'){
                      //if next char is P, set print to true
                    print = true;
                    ifile.get(x);
                  }
                  else{
                      //if next char is not a P, declare invalid command
                      skipline(ifile,x);
                      continue;
                  }
              } 
          }
          else if (x == 'P'){
              //if there is a P after the comma, set print = true, and get the next newline
              print = true;
              ifile.get(x);
          }
          else {
              //if the char after the comma is not a P or a B, declare invalid
              skipline(ifile,x);
              continue;
          }
      }
      //if end of command (no B or P), call drawing functions with respective parameters
      if (x == '\n' || ifile.eof()){ 
          if (dir == 'E' || dir == 'W'){
            drawLeftRight(ofile, penstatus, bold, num, dir, print);
        }
           else{
               drawUpDown(ofile, penstatus, bold, num, dir, print);
            }
      }
      else{
          //if no newline, no end of file, or no comma, declare invalid character
          skipline(ifile,x);
      }
   }
    //close all files
   ifile.close();
   ofile.close();
   infile.close();
   outfile.close();
}

