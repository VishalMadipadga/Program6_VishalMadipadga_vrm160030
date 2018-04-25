//Vishal Madipadga
//CS3377.501
//vrm160030@utdallas.edu
#include "cdk.h"
#include "program6.h"
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{
  //creating objects to store contents of binary file into
  BinaryFileHeader *headers = new BinaryFileHeader;
  BinaryFileRecord *records = new BinaryFileRecord;
  ifstream binaryFile ("cs3377.bin", ios::in | ios::binary);
  WINDOW        *window;
  CDKSCREEN     *cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 

  const char            *rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char            *columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
  int           boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int           boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
   */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
                          MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
			  boxTypes, 1, 1, ' ', ROW, true, true, false);
 
  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  //stringstream objects to convert bin file contents to strings
  stringstream versionStream;
  stringstream recordStream;
  stringstream magicStream;
  //reading from the binary file header section
  binaryFile.read((char *) headers, sizeof(BinaryFileHeader));

  //getting the magic number, converting it to hex and upper case
  magicStream<< uppercase << "0X" <<  hex << headers->magicNumber <<endl;
  //converting magic number to string
  string magic = magicStream.str();

  //getting version number and storing
  versionStream << headers -> versionNumber << endl;
  string version1 = versionStream.str();

  //getting number of records and storing
  recordStream << headers->numRecords << endl;
  string record1 = recordStream.str();

 //displaying bin file headers in matrix
  setCDKMatrixCell(myMatrix, 1, 1, ("Magic: "+magic ).c_str()  );
  setCDKMatrixCell(myMatrix, 1, 2, ("Version: " +  version1).c_str() );
  setCDKMatrixCell(myMatrix, 1, 3, ("NumRecords: "+ record1).c_str() );

  //reading from the bin file records section

  //i will be used to represent the row number of the matrix
  int i =2;
  //while the bin file is still reading valid data
   while( binaryFile.read((char *) records, sizeof(BinaryFileRecord))!= NULL)
   {
     //declaring a string stream object
     stringstream length;
     //casting strLength from the bin file to an int
     int stringLength = (int) records -> strLength;
     //passing strLength to the string stream
     length << stringLength << endl;
     string finalLength = length.str();
     //printing the strLength into the first column and string buffer into second column
     setCDKMatrixCell(myMatrix, i, 1, ("strlen: "+ finalLength).c_str());
     setCDKMatrixCell(myMatrix, i, 2, records -> stringBuffer);
     //incrementing i to point to point to the next row
     i++;
     //clearing string stream to be used again
     length.str(string());
     length.clear();
   }

  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
