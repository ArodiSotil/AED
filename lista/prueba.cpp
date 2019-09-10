#include <iostream>
using namespace std;

class persona
{
protected:
	string nombre;
	int edad;
public:
	persona(string n, int e){nombre = n; edad = e;}
	~persona();
	void setNombre(string nom){nombre = nom;}
	void setEdad(int ed){edad = ed;}
	string getNombre(){return nombre;}
	int getEdad(){return edad;}

};
class alumno: public persona
{
public:
	alumno(string n, int e , int no){nombre = n; edad = e; nota = no;}
	~alumno();
	void compara(){
		if(edad == 0)
			cout << "funciona";
	}
private:
	int nota;
	
};