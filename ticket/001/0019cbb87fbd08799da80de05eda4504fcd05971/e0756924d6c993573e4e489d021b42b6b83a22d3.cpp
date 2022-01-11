#include <plantenGui.h>
#include <wx/config.h>
#include <wx/datetime.h>
#include <plantenCmd.h>
#include <math.h>

#include <dataLayer.h>
#include <debug.h>

// On change of pane, a pane needs to be initialized, because the data
// part of the panes is shared!

// !!
//   All wxListCtrls should contain ids in lists instead of indices in lists
//   DON'T USE FindItem --> Poses problems in Windows! USE THE Static search
//   functions provided!
//   

static
int wxCALLBACK comparePlant(long item1, long item2, long sortData)
{
	// item1 --> Index in Plantenlijst
	// item2 --> Index in Plantenlijst
	
	dPlanten *d=(dPlanten *) sortData;
	wxString i1,i2;
	
	//debug("comparing item %d and %d\n",item1,item2);
	
	d->get(d->plantIndex(item1),i1);
	d->get(d->plantIndex(item2),i2);
	if (i1<i2) { return -1; }
	else if (i1>i2) { return 1; }
	else { return 0; }
}

static 
int doLstFindString(wxListCtrl *lst,wxString & S)
{
int i,n,index=-1;
	for(i=0,n=lst->GetItemCount();i<n && index==-1;i++) {
		wxString s;
		s=lst->GetItemText(i);
		if (s==S) { index=i; }
	}
return index;
}

static
int doLstFindId(wxListCtrl *lst,long id)
{
int i,n,index=-1;
	for(i=0,n=lst->GetItemCount();i<n && index==-1;i++) {
		long d;
		d=lst->GetItemData(i);
		if (d==id) { index=i; }
	}
return index;
}

void PlantenFrame::bestelInit(void)
{
	_currentBestelPlant="";
	_currentBestelMaat="";
	_currentBestelSoort="";
	_currentBestelPlantIndex=-1;
	_currentBestelMaatIndex=-1;
	
	if (bestelling!=NULL) { delete bestelling; }
	bestelling=new dBestellijst(getData()->db(),_currentObject);
	//bestelling->store();
	
	// Order is important
	
	bestelSetSoorten();
	bestelClearBestel();
	bestelClearFields();
	bestelClearObject();
	
	{
		wxConfig conf("Planten");
		_plantenFocus=conf.Read("plantenFocus",FOCUS_PLANTEN_NAAM);
	}
	
	bestelUpdateTotal();
	bestelFocus();
}


void PlantenFrame::bestelClearSoorten(void)
{
	chBestelPltSrt->Clear();
	bestelClearPlanten();
	_currentBestelSoort="";
}

void PlantenFrame::bestelSetSoorten(void)
{
int 				i,n;
wxString 			soort;
dPlantensoorten    *soorten=getData()->plantensoorten();
	
	bestelClearSoorten();
	soorten->fetch();
	for(i=0,n=soorten->len();i<n;i++) {
		soorten->get(i,soort);
		chBestelPltSrt->Append(soort);
	}
	if (n!=0) {
		chBestelPltSrt->SetSelection(0);
		soorten->get(0,soort);
		bestelDoSelectSoort(soort);
	}
}

void PlantenFrame::bestelGetSoort(wxString & soort)
{
	int i=chBestelPltSrt->GetSelection();
//	debug("%d\n",i);
	if (i==-1) { soort=""; }
	else {
		soort=chBestelPltSrt->GetStringSelection();
	}
}

void PlantenFrame::bestelDoSelectSoort(wxString & soort)
{
int					i,n;
wxString			plant;
dPlanten		   *planten=getData()->planten();
dPlantensoorten	   *soorten=getData()->plantensoorten();

	bestelClearPlanten();
	planten->fetch(soorten->key(soort));
	
	for(i=0,n=planten->len();i<n;i++) {
		planten->get(i,plant);
		long tmp=lstBestelPlanten->InsertItem(i,plant,0);
		lstBestelPlanten->SetItemData(tmp,planten->plantId(i));
	}
	lstBestelPlanten->SortItems(comparePlant,(long) getData()->planten());
	
	bestelFocusPlant();
	
	_currentBestelSoort=soort;
}

void PlantenFrame::bestelClearPlanten(void)
{
	lstBestelPlanten->ClearAll();
	if (lstBestelPlanten->GetColumnCount()==0) {
		lstBestelPlanten->InsertColumn(0,"Planten");
		int h,w;
		lstBestelPlanten->GetClientSize(&w,&h);
		w=(w*9)/10;
//		debug("lstBestelPlanten: h=%d, w=%d",h,w);
//		debug(", w<--%d\n",w);
		lstBestelPlanten->SetColumnWidth(0,w);
		lstBestelPlanten->SortItems(comparePlant,(long) getData()->planten());
	}
	
	bestelClearMaten();
}


void PlantenFrame::bestelSelectSoort(wxCommandEvent & event)
{
wxString soort;
	bestelGetSoort(soort);
	if (soort!=_currentBestelSoort) {
		bestelDoSelectSoort(soort);
	}
}


void PlantenFrame::bestelSelectPlant(wxListEvent & event)
{
	bestelDoSelectPlant(event.m_itemIndex);
	lstBestelPlanten->SetFocus();
}

void PlantenFrame::bestelDoDeselectCurrent(void)
{
	if (_currentBestelPlantIndex!=-1) {
		lstBestelPlanten->SetItemState(_currentBestelPlantIndex,0,wxLIST_STATE_SELECTED);
	}
}

void PlantenFrame::bestelDoSelectPlant(int index)
{
dPlanten 		*planten=getData()->planten();
dPlant  		*plant=getData()->plant();
wxString		 soort;
	
	lstBestelPlanten->SetItemState(index,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
	lstBestelPlanten->SetItemState(index,wxLIST_STATE_FOCUSED,wxLIST_STATE_FOCUSED);

	_currentBestelPlant=lstBestelPlanten->GetItemText(index);
	_currentBestelPlantIndex=index;
	
	bestelGetSoort(soort);
	
//	debug("plant = %s, soort = %s\n",(const char *) _currentBestelPlant,(const char *) soort);
//	debug("fetching %s\n",(const char *) planten->key(_currentBestelPlant));
	
	plant->fetch(planten->key(_currentBestelPlant));
	
//	debug("fetched\n");

	{
	int i,n=plant->len();
	wxString maat,prijs;
	double   dprijs;
	
		bestelClearMaten();
	
		for(i=0;i<n;i++) {
			plant->get(i,maat,dprijs);
			prijs=prijs.Format("%.2lf",dprijs);
			
			long tmp=lstBestelMaten->InsertItem(i,maat,0);
			lstBestelMaten->SetItemData(tmp,plant->maatId(i));
			lstBestelMaten->SetItem(tmp,1,prijs);			
		}
	}
	
	// set plantennaam and focus to next maat
	
	bestelClearFields();
	//** txtPlantenNaam->SetValue(_currentPlant);
	
	bestelDoSelectMaat(0);
	
	//plantenNextMaat();  DO NOT SET FOCUS, PLANTEN LIST WON'T ACCEPT KEYS!
}

void PlantenFrame::bestelLstPlantenScroll(int index)
{
dPlanten *planten=getData()->planten();
	int l=(index-5)<0 ? 0 : index-5;
	int u=(index+5)>=planten->len() ? planten->len()-1 : index+5;
	
	lstBestelPlanten->EnsureVisible(l);
	lstBestelPlanten->EnsureVisible(u);
}


void PlantenFrame::bestelPlantKeuze(wxCommandEvent & event)
{
wxString  plant=txtBestelPlantKeuze->GetValue().Trim().MakeLower();
dPlanten *planten=getData()->planten();
int       index;
	
	if (planten->len()>0) {
		index=findPlant(lstBestelPlanten,planten,0,planten->len(),plant);
		if (index>=planten->len()) { index=planten->len()-1; }
		if (index<0) { index=0; }
		
		if (index!=_currentBestelPlantIndex) {
			bestelLstPlantenScroll(index);
			bestelDoDeselectCurrent();
			bestelDoSelectPlant(index);
			txtBestelPlantKeuze->SetFocus();
		}
	}
}

void PlantenFrame::bestelClearMaten(void)
{
	lstBestelMaten->ClearAll();
	if (lstBestelMaten->GetColumnCount()==0) {
		lstBestelMaten->InsertColumn(0,"Maat");
		lstBestelMaten->InsertColumn(1,"Prijs",wxLIST_FORMAT_RIGHT);
		int h,w;
		lstBestelMaten->GetClientSize(&w,&h);
		w=(w*9)/10;
		lstBestelMaten->SetColumnWidth(0,w/2);
		lstBestelMaten->SetColumnWidth(1,w/2);
	}
	bestelClearFields();
	
	_currentBestelMaat="";
	_currentBestelMaatIndex=-1;
}

void PlantenFrame::bestelDoSelectMaat(int index)
{
dPlant  *plant=getData()->plant();
wxString maat;
double   dprijs;
	
	if (_currentBestelMaatIndex!=-1 && _currentBestelMaatIndex!=index) {
		lstBestelMaten->SetItemState(_currentBestelMaatIndex,0,wxLIST_STATE_SELECTED);
	}
	lstBestelMaten->SetItemState(index,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);

	{int id=lstBestelMaten->GetItemData(index);
	 int i=plant->maatIndex(id);
		plant->get(i,maat,dprijs);
	}

	_currentBestelMaat=maat;
	_currentBestelMaatIndex=index;

	//bestelFocusAantal();
}

void PlantenFrame::bestelSelectMaat(wxListEvent & event)
{
int index=event.m_itemIndex;
	bestelDoSelectMaat(index);
}

void PlantenFrame::bestelFocusAantal(void)
{
	bestelFocus(FOCUS_PLANTEN_PRIJS);
}

void PlantenFrame::bestelFocusPlant(void)
{
	bestelFocus(FOCUS_PLANTEN_NAAM);
}

void PlantenFrame::bestelFocus(int focus)
{
	wxTextCtrl *T;
	
	if (focus==-1) {
		focus=_plantenFocus;
	}
	
	if (focus==FOCUS_PLANTEN_NAAM) {
		T=txtBestelPlantKeuze;
	}
	else {
		T=txtBestelAantal;
	}
	
	T->SetFocus();
	int l=T->GetLineLength(0);
	T->SetSelection(l,l);
	
}

void PlantenFrame::bestelClearFields(void)
{
	txtBestelAantal->SetValue("");
}

void PlantenFrame::bestelClearObject(void)
{
	lblDorp->SetLabel("");
	lblObject->SetLabel("");
	lblRekNr->SetLabel("");
	lblTekNr->SetLabel("");
}

////////////////////////////////////////////////////////

void PlantenFrame::bestelToBestelling(void)
{
wxString object,dorp,reknr,teknr;
wxString key;
	
	getObjGeg(dorp,object,reknr,teknr);
	dObject o(dorp,object,reknr,teknr);
	
	bestelling->setObject(o);
}


////////////////////////////////////////////////////////

void PlantenFrame::bestelEnable(bool enable)
{
	chBestelPltSrt->Enable(enable);
	txtBestelPlantKeuze->Enable(enable);
	lstBestelPlanten->Enable(enable);
	lstBestelMaten->Enable(enable);
	txtBestelAantal->Enable(enable);
	btBestelVerwijderen->Enable(enable);
	btBestelToevoegen->Enable(enable);
	btBestelAanpassen->Enable(enable);
	btUpdatePrices->Enable(enable);
	btObjectGeg->Enable(enable);
	lstBestellijst->Enable(enable);
}

void PlantenFrame::OnMenuBestelNieuw(wxCommandEvent & event)
{
bool sure=true;
	if (!bestelling->empty() && bestelling->changed()) {
		if (wxMessageBox("De huidige bestellijst is gewijzigd, wijzigingen opslaan?"
			             ,"Plantenlijsten",
					wxYES_NO | wxICON_INFORMATION|wxCENTRE, this)==wxYES) 
		{
						bestelling->store();
		}
	}
	
	if (sure) {
		// Objecten lezen
		
		dObjecten *objecten=getData()->objecten();
		
		objecten->fetch();
		
		dlgObjectGeg *dlg=new dlgObjectGeg(this,-1,"Object Gegevens");
		dlg->setData(objecten);
		
		if (dlg->ShowModal()==wxID_OK) {
			wxString dorp,object,reknr,teknr;
			
			// order
			
			dlg->get(dorp,object,reknr,teknr);
			debug("Nieuw: dorp:%s object:%s reknr:%s teknr:%s\n",
						(const char *) dorp,
						(const char *) object,
						(const char *) reknr,
						(const char *) teknr
			);
			
			_currentObject.set(dorp,object,reknr,teknr);
			_openedObjectAs=_currentObject;
			
			objecten->add(_currentObject);
			objecten->sort();
			objecten->store();
			
			// is 
			
			bestelInit();
			
			// important
			
			lblObject->SetLabel(object);
			lblDorp->SetLabel(dorp);
			lblRekNr->SetLabel(reknr);
			lblTekNr->SetLabel(teknr);
			
			bestelEnable();
		}
	}
}

void PlantenFrame::OnMenuBestelBewaren(wxCommandEvent & event)
{
bool sure=true;
	if (bestelling->valid()) {
		if (sure) {
			bestelling->store();
			if (_openedObjectAs!=_currentObject) {
				dBestellijst *B=new dBestellijst(getData()->db(),_openedObjectAs);
				B->remove();
				_openedObjectAs=_currentObject;
				
				wxDateTime dt;
				dt.SetToCurrent();
				wxString s="De huidige bestellijst is bewaard om "+dt.FormatISODate()+", "+dt.FormatISOTime()+".";
				sbPlantenStatus->SetStatusText(s);
			}
		}
	}
}

void PlantenFrame::OnMenuBestelVerwijderen(wxCommandEvent & event)
{
bool sure=true;
	if (!_currentObject.valid()) {
		wxMessageBox("Er is geen bestellijst geopend die kan worden verwijderd","Bestellijsten",
				wxOK | wxICON_INFORMATION|wxCENTRE, this);		
		sure=false;
	}
	else {
		sure=wxMessageBox("Weet u zeker dat u de huidige bestellijst wilt verwijderen?","Bestellijsten",
				wxYES_NO | wxICON_QUESTION|wxCENTRE, this)==wxYES;
	}
	
	if (sure) {
		// Remove object
		
		dObjecten *objecten=getData()->objecten();
		objecten->fetch();
		
		{
			wxString dorp,object,reknr,teknr;
			_currentObject.get(dorp,object,reknr,teknr);
//			debug("%s %s %s %s\n",(const char *) dorp,(const char *) object,(const char *) reknr,(const char *) teknr);
		}
		objecten->remove(_currentObject);
		bestelling->remove();
		objecten->store();
	
		// Clean up
		
		dObject d;
		_currentObject=d;
		bestelInit();
		bestelEnable(false);
	}
	
}


void PlantenFrame::OnMenuBestelOpenen(wxCommandEvent & event)
{
bool sure=true;
	if (!bestelling->empty() && bestelling->changed()) {
		if (wxMessageBox("De huidige bestellijst is gewijzigd, wijzigingen opslaan?"
			             ,"Plantenlijsten",
					wxYES_NO | wxICON_INFORMATION|wxCENTRE, this)==wxYES) 
		{
						bestelling->store();
		}
	}
	
	if (sure) {
		// Objecten dialoog openen
		
		dObjecten *objecten=getData()->objecten();
		
		objecten->fetch();
		objecten->sort();
		
		dlgObjecten *dlg=new dlgObjecten(this,-1,"Bestellijsten");
		dlg->setData(objecten);
		
		if (dlg->ShowModal()==wxID_OK) {
			wxString dorp,object,reknr,teknr;
			
			dlg->getObject(_currentObject);
			
			// Order
			
			_currentObject.get(dorp,object,reknr,teknr);
			_openedObjectAs=_currentObject;
			
			// is
			
			bestelInit();
			
			// important
			
			bestelling->fetch();
			
			lblDorp->SetLabel(dorp);
			lblObject->SetLabel(object);
			lblRekNr->SetLabel(reknr);
			lblTekNr->SetLabel(teknr);
			
//			debug("ok fetched,%d\n",bestelling->len());
			
			bestelMakeBestel();
			
			bestelEnable();
		}
	}
}


void PlantenFrame::OnBestelObjectGeg(wxCommandEvent & event)
{
	if (bestelling->valid()) {
		wxString dorp,object,reknr,teknr;
		
		dObjecten *objecten=getData()->objecten();
		objecten->fetch();
		
		dlgObjectGeg *dlg=new dlgObjectGeg(this,-1,"Object Gegevens");
		
		dlg->setData(objecten);
		
		getObjGeg(dorp,object,reknr,teknr);
		dlg->set(dorp,object,reknr,teknr);
		
		if (dlg->ShowModal()==wxID_OK) {
			dlg->get(dorp,object,reknr,teknr);
			lblObject->SetLabel(object);
			lblDorp->SetLabel(dorp);
			lblRekNr->SetLabel(reknr);
			lblTekNr->SetLabel(teknr);
			
			dObject o(dorp,object,reknr,teknr);
			
			objecten->change(_currentObject,o);
			
			_currentObject=o;
			bestelling->setObject(_currentObject);
			
			objecten->store();
		}
	}
}

void PlantenFrame::getObjGeg(wxString & dorp, wxString & object, wxString & reknr, wxString & teknr)
{
	dorp=lblDorp->GetLabel().Trim().MakeLower();
	object=lblObject->GetLabel().Trim().MakeLower();
	reknr=lblRekNr->GetLabel().Trim().MakeLower();
	teknr=lblTekNr->GetLabel().Trim().MakeLower();
}

void PlantenFrame::bestelUpdatePrices(wxCommandEvent & event)
{
	if (bestelling->valid()) {
		bestelling->updatePrijzen();
		bestelMakeBestel();
	}
}

/************************************************************************/

void PlantenFrame::bestelClearBestel(void)
{
	
	// Store column settings of lstBestellijst.
	
	if (!_firstBestelDisplay)
	{
	 wxConfig conf("Planten");
		conf.Write("lstBestellijst_soort",(long) lstBestellijst->GetColumnWidth(0));
		conf.Write("lstBestellijst_plant",(long) lstBestellijst->GetColumnWidth(1));
		conf.Write("lstBestellijst_maat",(long) lstBestellijst->GetColumnWidth(2));
		conf.Write("lstBestellijst_aantal",(long) lstBestellijst->GetColumnWidth(3));
		conf.Write("lstBestellijst_prijs",(long) lstBestellijst->GetColumnWidth(4));
	}
	
	lstBestellijst->ClearAll();
	if (lstBestellijst->GetColumnCount()==0) {
		lstBestellijst->InsertColumn(0,"Soort");
		lstBestellijst->InsertColumn(1,"Plant");
		lstBestellijst->InsertColumn(2,"Maat");
		lstBestellijst->InsertColumn(3,"Aantal",wxLIST_FORMAT_RIGHT);
		lstBestellijst->InsertColumn(4,"Prijs",wxLIST_FORMAT_RIGHT);
		
		{
		 wxConfig conf("Planten");
		 long cSoort,cPlant,cMaat,cAantal,cPrijs;
			cSoort=conf.Read("lstBestellijst_soort",-1);
			cPlant=conf.Read("lstBestellijst_plant",-1);
			cMaat=conf.Read("lstBestellijst_maat",-1);
			cAantal=conf.Read("lstBestellijst_aantal",-1);
			cPrijs=conf.Read("lstBestellijst_prijs",-1);
			
			if (cSoort!=-1) {
				lstBestellijst->SetColumnWidth(0,cSoort);
				lstBestellijst->SetColumnWidth(1,cPlant);
				lstBestellijst->SetColumnWidth(2,cMaat);
				lstBestellijst->SetColumnWidth(3,cAantal);
				lstBestellijst->SetColumnWidth(4,cPrijs);
			}
		}
	}
	_firstBestelDisplay=false;
}

static
int wxCALLBACK bestelCompareLines(long item1, long item2, long sortData)
{
	// item1 --> Index in Plantenlijst
	// item2 --> Index in Plantenlijst
	
	dBestellijst *b=(dBestellijst *) sortData;
	wxString s1,s2,p1,p2,m1,m2;
	int a1,a2;
	double pr1,pr2;
	
	b->get(b->lineIndex(item1),s1,p1,m1,a1,pr1);
	b->get(b->lineIndex(item2),s2,p2,m2,a2,pr2);
	
	if (s1<s2) { return -1; }
	else if (s1==s2) {
		if (p1<p2) { return -1; }
		else if (p1==p2) {
			if (m1<m2) { return -1; }
			else if (m1==m2) { return 0; }
		}
	}
return 1;	
}

void PlantenFrame::bestelUpdateTotal(void)
{
double total=0;
wxString t;
	bestelling->total(total);
	t=t.Format("%.2lf",total);
	lblBestelTotaal->SetLabel(t);
}


void PlantenFrame::insLine(int i,int id,
							wxString & soort, wxString & plant, wxString & maat, 
							int aantal,double prijs,
							bool sort
						  )
{
wxString _aant,_prijs;
	
	prijs*=aantal;
	_aant=_aant.Format("%d",aantal);
	_prijs=_prijs.Format("%.2lf",prijs);

	long tmp=lstBestellijst->InsertItem(i,soort,0);
	lstBestellijst->SetItemData(tmp,id);
	lstBestellijst->SetItem(tmp,1,plant);
	lstBestellijst->SetItem(tmp,2,maat);
	lstBestellijst->SetItem(tmp,3,_aant);
	lstBestellijst->SetItem(tmp,4,_prijs);
	
	if (sort) { lstBestellijst->SortItems(bestelCompareLines,(long) bestelling); }
	
	bestelUpdateTotal();
}

void PlantenFrame::updateLine(wxString & soort, wxString & plant, wxString & maat, int aantal, double prijs)
{
int      i,n;
wxString _aant,_prijs;
bool     found=false;
wxString s,p,m;
int      a;
double   pr;

	prijs*=aantal;
	
	i=0;n=bestelling->len();
	do {
		bestelling->get(i,s,p,m,a,pr);
		if (s==soort && p==plant && m==maat) { found=true; }
		else {
			i+=1;
		}
	} while (i<n && !found);
	
	if (found) {
		_aant=_aant.Format("%d",aantal);
		_prijs=_prijs.Format("%.2lf",prijs);
		
		int index=doLstFindId(lstBestellijst,bestelling->lineId(i)); //lstBestellijst->FindItem(-1,i);
		
		lstBestellijst->SetItem(index,0,soort);
		lstBestellijst->SetItem(index,1,plant);
		lstBestellijst->SetItem(index,2,maat);
		lstBestellijst->SetItem(index,3,_aant);
		lstBestellijst->SetItem(index,4,_prijs);
	}
	
	bestelUpdateTotal();
}

void PlantenFrame::removeLine(wxString & soort, wxString & plant, wxString & maat)
{
int      i,n;
bool     found=false;
wxString s,p,m;
int      a;
double   pr;
	
	i=0;n=bestelling->len();
	do {
		bestelling->get(i,s,p,m,a,pr);
		if (s==soort && p==plant && m==maat) { found=true; }
		else {
			i+=1;
		}
	} while (i<n && !found);
	
	if (found) {
		int index=doLstFindId(lstBestellijst,bestelling->lineId(i));  //lstBestellijst->FindItem(-1,i);
		lstBestellijst->DeleteItem(index);
	}
	
	//bestelUpdateTotal(); Dit heeft geen zin, bestelling is nog niet verwijderd uit de bestellijst.
}

void PlantenFrame::bestelSelectLine(wxListEvent & event)
{
int index=event.m_itemIndex;
wxString soort,plant,maat,aantal;
int    aant;
double prijs;
bool update=false;
int I;
	
//	debug("bestelling: %p\n",bestelling);
	
	I=lstBestellijst->GetItemData(index);
//	debug("get %d\n",I);
	bestelling->get(bestelling->lineIndex(I),soort,plant,maat,aant,prijs);
	debug("get: index=%d, I=%d, %s, %s, %s, %d, %.2lf\n",
			index,I,
			(const char *) soort,
			(const char *) plant,
			(const char *) maat,
			aant,
			prijs
		);
//	debug("get %d ok\n",I);
	aantal=aantal.Format("%d",aant);
	
//	debug("%d, %s\n",aant,(const char *) aantal);
	
	if (soort!=_currentBestelSoort) {
		bestelDoSelectSoort(soort);
		int i=chBestelPltSrt->FindString(soort);
		chBestelPltSrt->SetSelection(i);
		update=true;
	}
	
	if (update || plant!=_currentBestelPlant) {
		//int i=lstBestelPlanten->FindItem(-1,plant);
		int i=doLstFindString(lstBestelPlanten,plant);
		{
			wxString s;
			s=lstBestelPlanten->GetItemText(i);
			debug("Found plant %d, plant='%s', found='%s'\n",i,(const char *) plant,(const char *) s);
		}
		bestelLstPlantenScroll(i);
		bestelDoDeselectCurrent();
		bestelDoSelectPlant(i);
		update=true;
	}
	
	if (update || maat!=_currentBestelMaat) {
		int i=doLstFindString(lstBestelMaten,maat);
		bestelDoSelectMaat(i);
	}
	
	txtBestelAantal->SetValue(aantal);
	bestelFocusAantal();
}


void PlantenFrame::bestelMakeBestel(void)
{
wxString soort, plant,maat;
int aantal;
double prijs;
int i;
	
	bestelClearBestel();
	for(i=0;i<bestelling->len();i++) {
		bestelling->get(i,soort,plant,maat,aantal,prijs);
		insLine(i,bestelling->lineId(i),soort,plant,maat,aantal,prijs,false);
	}
	lstBestellijst->SortItems(bestelCompareLines,(long) bestelling);
	
	if (bestelling->prijzenOk()) {
		lblNeedsUpdating->SetLabel("");
	}
	else {
		lblNeedsUpdating->SetLabel("!GEEN ACTUELE PRIJZEN!");
	}
}

/************************************************************************/

void PlantenFrame::bestelToevoegen(wxCommandEvent & event)
{
	bestelToevoegenAanpassen(true);
}

void PlantenFrame::bestelToevoegenAanpassen(bool add)
{
bool ok=true;
	
	// validation
	
	if (_currentBestelPlant=="" || _currentBestelMaat=="" || _currentBestelSoort=="") {
		wxMessageBox("U dient een soort,plant,maat combinatie te selecteren.","Bestellijsten",
				wxOK | wxICON_INFORMATION|wxCENTRE, this);		
		ok=false;
	}
	
	wxString aantal;
	aantal=txtBestelAantal->GetValue().Trim();
	if (!aantal.IsNumber() || aantal=="") {
		wxMessageBox("Er is geen goed aantal opgegeven voor de soort,plant,maat combinatie.","Bestellijsten",
				wxOK | wxICON_INFORMATION|wxCENTRE, this);		
		ok=false;
	}
	
	// adding or updating
	
	if (ok) {
		int soortId,plantId,maatId,aant;
		dPlantensoorten *soorten=getData()->plantensoorten();
		dPlanten        *planten=getData()->planten();
		dPlant          *plant=getData()->plant();
		bool   existed;
		
		soortId=soorten->soortId(_currentBestelSoort);
		plantId=planten->plantId(_currentBestelPlant);
		maatId=plant->maatId(_currentBestelMaat);
		{long a;
			aantal.ToLong(&a);
			aant=a;
		}
		
		existed=bestelling->exists(soortId,plantId,maatId);
		if (existed) {
			bestelling->update(soortId,plantId,maatId,aant);
		}
		else if (add) {
			bestelling->add(soortId,plantId,maatId,aant);
		}
		else {
			ok=false;
		}
		
		if (ok) {
			{wxString s,p,m;
			 int aantal;
			 double prijs;
				bestelling->get(soortId,plantId,maatId,s,p,m,aantal,prijs);
				
				if (existed) {
					updateLine(s,p,m,aantal,prijs);
				}
				else if (add) {
					int n=bestelling->len()-1;
					insLine(n,bestelling->lineId(n),s,p,m,aantal,prijs);
				}
			}
			
			bestelClearFields();
		}
		else {
			wxMessageBox("Er is geen bestelregel om aan te passen voor deze soort,plant,maat combinatie.","Bestellijsten",
				wxOK | wxICON_INFORMATION|wxCENTRE, this);		
		}
	}
	
	bestelFocusAantal();
}

void PlantenFrame::bestelAanpassen(wxCommandEvent & event)
{
	bestelToevoegenAanpassen(false);
}


void PlantenFrame::bestelVerwijderen(wxCommandEvent & event)
{
bool ok=true;
	
	// validation
	
	if (_currentBestelPlant=="" || _currentBestelMaat=="" || _currentBestelSoort=="") {
		wxMessageBox("U dient een soort,plant,maat combinatie te selecteren.","Bestellijsten",
				wxOK | wxICON_INFORMATION|wxCENTRE, this);		
		ok=false;
	}
	
	// Removing
	
	if (ok) {
		int soortId,plantId,maatId;
		dPlantensoorten *soorten=getData()->plantensoorten();
		dPlanten        *planten=getData()->planten();
		dPlant          *plant=getData()->plant();
		bool   existed;
		
		debug("soort=%s, plant=%s, maat=%s\n",
				(const char *) _currentBestelSoort,
				(const char *) _currentBestelPlant,
				(const char *) _currentBestelMaat
			);
		
		soortId=soorten->soortId(_currentBestelSoort);
		plantId=planten->plantId(_currentBestelPlant);
		maatId=plant->maatId(_currentBestelMaat);
		
		existed=bestelling->exists(soortId,plantId,maatId);
		if (existed) {
			{wxString s,p,m;
			 int aantal;
			 double prijs;
				bestelling->get(soortId,plantId,maatId,s,p,m,aantal,prijs);
				removeLine(s,p,m);
				debug("soort=%s, plant=%s, maat=%s\n",
						(const char *) s,
						(const char *) p,
						(const char *) m
					);
			}
			bestelling->remove(soortId,plantId,maatId);
			bestelUpdateTotal();
		}
		else {
			wxMessageBox("Er is geen bestelregel om aan verwijderen voor deze soort,plant,maat combinatie.","Bestellijsten",
				wxOK | wxICON_INFORMATION|wxCENTRE, this);		
		}
	}
}




 	  	 
