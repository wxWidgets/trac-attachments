#include <unistd.h>
#include <sys/param.h>
#include <iostream>

using namespace std;

int main(int, char **)
{
  // Gets logical path.
  char path[MAXPATHLEN];
  getcwd(path, MAXPATHLEN);
  cout << "Logical path = " << path << endl;

  // Gets physical path.
  unsetenv("PWD");
  getcwd(path, MAXPATHLEN);
  cout << "Physical path = " << path << endl;

  return 0;
}


 	  	 
