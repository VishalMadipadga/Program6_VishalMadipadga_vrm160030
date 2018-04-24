#include <iostream>
#include "cdk.h"
#include "program6.h"
#include <fstream>
#include <string>
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{
  BinaryFileHeader *headers = new BinaryFileHeader;
  BinaryFileRecord *records = new BinaryFileRecord;
  ifstream binaryFile ("cs3377.bin", ios::in | ios::binary);
  WINDOW        *window;
  CDKSCREEN     *cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

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

  /*
   * Dipslay a message
   */
  stringstream ss;
  stringstream sss;
  binaryFile.read((char *) headers, sizeof(BinaryFileHeader));

  int version = (int) headers->versionNumber;
  ss << version << endl;
  string version1 = ss.str();

  int record = (int) headers->numRecords;
  sss << record << endl;
  string record1 = sss.str();

 
  setCDKMatrixCell(myMatrix, 1, 1, "Magic: "   );
  setCDKMatrixCell(myMatrix, 1, 2, ("Version: " +  version1).c_str() );
  setCDKMatrixCell(myMatrix, 1, 3, ("NumRecords: "+ record1).c_str() );

  binaryFile.read((char *) records, sizeof(BinaryFileRecord));

  stringstream length;
  int stringLength = (int) records -> strLength;
  length << stringLength << endl;
  string stringLength1 = length.str();

  setCDKMatrixCell(myMatrix, 2, 1, ("strlen: "+ stringLength1).c_str());
  setCDKMatrixCell(myMatrix, 2, 2,  records -> stringBuffer);

 binaryFile.read((char *) records, sizeof(BinaryFileRecord));


   stringstream length1;
   int stringLength2 = (int) records -> strLength;
   length1 << stringLength2 << endl;
   string stringLength3 = length1.str();

  setCDKMatrixCell(myMatrix, 3, 1, ("strlen: "+ stringLength3).c_str());
  setCDKMatrixCell(myMatrix, 3, 2, records -> stringBuffer);


   binaryFile.read((char *) records, sizeof(BinaryFileRecord));


  stringstream length2;
  int stringLength4 = (int) records -> strLength;
  length2 << stringLength4 << endl;
  string stringLength5 = length2.str();

  setCDKMatrixCell(myMatrix, 4, 1, ("strlen: "+ stringLength5).c_str());
  setCDKMatrixCell(myMatrix, 4, 2, records -> stringBuffer);




 binaryFile.read((char *) records, sizeof(BinaryFileRecord));


   stringstream length3;
   int stringLength6 = (int) records -> strLength;
   length3 << stringLength6 << endl;
   string stringLength7 = length3.str();

   setCDKMatrixCell(myMatrix, 5, 1, ("strlen: "+ stringLength7).c_str());
   setCDKMatrixCell(myMatrix, 5, 2, records -> stringBuffer);

  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
