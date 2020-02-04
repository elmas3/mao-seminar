/*========================================================

	[LineManager.h]
	Author : o‡ãÄ‘¾

=========================================================*/

#pragma once
#include "Line.h"

class LineManager
{
private:
	Topline m_Topline;
	Underline m_Underline;                                                                                                           
	Leftline m_Leftline;
	Rightline m_Rightline;
public:
	void  Set();
	Topline* Gettopline();
	Underline* Getunderline();
	Leftline* Getleftline();
	Rightline* Getrightline();
};

