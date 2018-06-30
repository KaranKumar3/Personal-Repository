#include<iostream>
#include<string>

using namespace std;
//assembly code: g++ --std=c++11 -pedantic -Wall p1.cpp

class movie {
	public:
		string title;
		string director;
		int year;
		string rating;
		
		//Constructor
		movie(string name, string dir, int yr, string rat) {
			title = name;
			director = dir;
			year = yr;
			rating = rat;
		}
	void print_movie(movie m) {
		
		cout << "Title:" << m.title << endl;
		cout << "Director:" << m.director << endl;
		cout << "Year:" << m.year << endl;
		cout << "Rating:" << m.rating << endl;
	}

};

int main () {
	
  movie avengers("The Avengers", "Joss Whedon", 2012, "PG-13");
  
  printf("Movie 1\n");
  avengers.print_movie(avengers);
  
  movie lincoln("Lincoln", "Steven Spielberg", 2012, "PG-13");
  
  movie *mptr;
  
  mptr = &lincoln;
  
  printf("\nMovie 2\n");
  lincoln.print_movie(*mptr);
  
  return 0;
}