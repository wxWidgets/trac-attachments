#include <wx/fileconf.h>

int main(){
	wxConfigBase * cfg;
	wxString sPath, sValueName, sValue;

	cfg = new wxFileConfig("test", "tester", "test.ini", "test.ini", wxCONFIG_USE_RELATIVE_PATH);
	sPath = "A";
	cfg->SetPath("/Testing/" + sPath);
	sValueName = "1";
	sValue = sValueName;
	sValue.Append(" Value");
	cfg->Write(sValueName, sValue);
	cfg->SetPath("/Testing/" + sPath + "/SubTesting/");
	sValueName = "1";
	sValue = sValueName;
	sValue.Append(" Value");
	cfg->Write(sValueName, sValue);
	
	sPath = "B";
	cfg->SetPath("/Testing/" + sPath);
	sValueName = "1";
	sValue = sValueName;
	sValue.Append(" Value");
	cfg->Write(sValueName, sValue);
	cfg->SetPath("/Testing/" + sPath + "/SubTesting/");
	sValueName = "1";
	sValue = sValueName;
	sValue.Append(" Value");
	cfg->Write(sValueName, sValue);
	
	sPath = "C";
	cfg->SetPath("/Testing/" + sPath);
	sValueName = "1";
	sValue = sValueName;
	sValue.Append(" Value");
	cfg->Write(sValueName, sValue);
	cfg->SetPath("/Testing/" + sPath + "/SubTesting/");
	sValueName = "1";
	sValue = sValueName;
	sValue.Append(" Value");
	cfg->Write(sValueName, sValue);
	delete cfg;

	cfg = new wxFileConfig("test", "tester", "test.ini", "test.ini", wxCONFIG_USE_RELATIVE_PATH);
	cfg->SetPath("/Testing/");
	int num_groups = cfg->GetNumberOfGroups();
	int i;
	for(i = 0; i < num_groups; i++){
		wxString str;
		long ind;
		cfg->SetPath("/Testing/");
		cfg->GetFirstGroup(str, ind);
		printf("%s\n", str);
		// ************ comment next line for proper running
		cfg->SetPath("/Testing/" + str + "/SubTesting/");
		cfg->DeleteGroup("/Testing/" + str);
	}
	delete cfg;
	return 0;
}

 	  	 
