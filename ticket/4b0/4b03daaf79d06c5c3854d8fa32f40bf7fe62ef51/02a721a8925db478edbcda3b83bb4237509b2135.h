/*!
 * \file LayoutProblem.h
 * \author Elias Gerber <egerber@gmx.net>
 * \date 19.05.2013
 * 
 * [Brief Header-file description]
 */ 

#pragma once
#ifndef LAYOUTPROBLEM_H
#define LAYOUTPROBLEM_H


// Classes
// -------
class LayoutProblem
	: public wxApp
{
public:
	virtual bool OnInit();

	wxPanel*		m_pPanel;

	wxStaticText*	m_pLbl1;

	wxButton*		m_pBtn1;

	void OnButton1(wxCommandEvent& event); 
};

DECLARE_APP(LayoutProblem);

#endif // LAYOUTPROBLEM_H
