// MyJsonSchriftfilter.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "json/reader.h"
#include "json/writer.h"
#include "json/elements.h"
#include <io.h>
#include "iostream"
#include "fstream"
using namespace json;


int _tmain(int argc, _TCHAR* argv[])
{
	/////////////////////////////////
	//Creating Json
	auto a = 5;
	auto b = 5;
	auto c = 10;
	auto d = 10;
	auto identi = 20;

	Object objDocument;
	objDocument["Multimatch"]["a"]["P1.x"] = Number(a);
	objDocument["Multimatch"]["a"]["P1.y"] = Number(b);
	objDocument["Multimatch"]["a"]["P2.x"] = Number(c);
	objDocument["Multimatch"]["a"]["P2.y"] = Number(d);
	objDocument["Multimatch"]["a"]["Identify"] = Number(identi);

	objDocument["Schriftfilter"]["b"]["P1.x"] = Number(a);
	objDocument["Schriftfilter"]["b"]["P1.y"] = Number(b);
	objDocument["Schriftfilter"]["b"]["P2.x"] = Number(c);
	objDocument["Schriftfilter"]["b"]["P2.y"] = Number(d);
	objDocument["Schriftfilter"]["b"]["Identify"] = Number(identi);
	auto& objRoot = objDocument;

	//////////////////////////////////
	//Showing json
	const Number numAbv1 = objRoot["Multimatch"]["a"]["P1.x"];
	const Number numAbv2 = objRoot["Multimatch"]["a"]["P1.y"];
	const Number numAbv3 = objRoot["Multimatch"]["a"]["P2.x"];
	const Number numAbv4 = objRoot["Multimatch"]["a"]["P2.y"];
	const Number& Identi0 = objRoot["Multimatch"]["a"]["Identify"];

	std::cout << "Multimatch" << "a" << " p1.x: " << numAbv1.Value() << std::endl;
	std::cout << "Multimatch" << "a" << " p1.y: " << numAbv2.Value() << std::endl;
	std::cout << "Multimatch" << "a" << " p2.x: " << numAbv3.Value() << std::endl;
	std::cout << "Multimatch" << "a" << " p2.y: " << numAbv4.Value() << std::endl;
	std::cout << "Multimatch" << "a" << " Identify: " << Identi0.Value() << std::endl;
	std::cout << "JsoninsideNumber" << 1 << std::endl;

	////////////////////////////////////
	// Writing Json
	std::cout << "Writing file out...\n";
	std::ofstream file("Jsonout.json", std::ios::out | std::ios::ate);
	if (!file)
	{
		std::cout << "Can not open the file" << std::endl;
		exit(1);
	}
	Writer::Write(objRoot, file);
	file.close();

	////////////////////////////////////
	//Reading jsonfile 
	std::cout << "then reading it back in.\n" << std::endl;
	std::ifstream myjson_file("Jsonout.json", std::ifstream::binary);
	Object elemRootFile;
	Reader::Read(elemRootFile, myjson_file);
	const Number numAbvout = elemRootFile["Multimatch"]["a"]["P1.x"];
	std::cout << "Multimatch" << "out" << " p1.x: " << numAbvout.Value() << std::endl;

	/////////////////////////////////////
	// check if exit and remove 
	std::cout << "Check and Remove the object......\n";
	if (const Boolean& Schriftfilterexist= elemRootFile["Schriftfilter"])
	{
		Object& arraySchriftfilter = elemRootFile["Schriftfilter"];
		arraySchriftfilter.Erase(arraySchriftfilter.Begin());
	}
	if (const Boolean& Multiexist = elemRootFile["Multimatch"])
	{
		Object& objmuti = elemRootFile["Multimatch"];
		objmuti.Erase(objmuti.Begin());
	}

	/////////////////////////////////////////
	// Rewriting the Json
	std::cout << "ReWriting file out...\n";

	elemRootFile["Multimatch"]["a"]["P1.x"] = Number(2000);
	elemRootFile["Multimatch"]["a"]["P1.y"] = Number(2000);
	elemRootFile["Multimatch"]["a"]["P2.x"] = Number(2000);
	elemRootFile["Multimatch"]["a"]["P2.y"] = Number(2000);
	elemRootFile["Multimatch"]["a"]["Identify"] = Number(5000);

	elemRootFile["Schriftfilter"]["b"]["P1.x"] = Number(1000);
	elemRootFile["Schriftfilter"]["b"]["P1.y"] = Number(1000);
	elemRootFile["Schriftfilter"]["b"]["P2.x"] = Number(1000);
	elemRootFile["Schriftfilter"]["b"]["P2.y"] = Number(1000);
	elemRootFile["Schriftfilter"]["b"]["Identify"] = Number(5000);

	
	std::ofstream Rewritefile("Jsonout.json", std::ios::out | std::ios::ate);
	if (!Rewritefile)
	{
		std::cout << "Can not open the file" << std::endl;
		exit(1);
	}
	Writer::Write(elemRootFile, Rewritefile);
	Rewritefile.close();
	getchar();
	return 0;
}

