/**
 * Build Command
 * wxGTK: g++ a.cpp -std=gnu++11 -Wall $(wx-config --cxxflags --libs core,base)
 * wxMSW: g++ a.cpp -std=gnu++11 -Wall $(wx-config --cxxflags core,base) -lgdi32 -lcomdlg32 -lwx_mswu_core-3.0 -lwx_baseu-3.0
 */
#include <cstdio>
#include <ctime>
#include <wx/wx.h>

/**
 * These codes are miscellaneous and not important.
 * They are for showing debugging message only.
 * They don't depend on wxWidgets.
 */
FILE *g_fh(void)
{
	static struct SFile {
		SFile() {
			m_fh = ::fopen("threads.log", "w");
		}
		~SFile() {
			::fclose(m_fh);
		}
		FILE *m_fh;
	} s_fout;
	return s_fout.m_fh;
}
const char *timestamp(void)
{
	static const size_t cchBuf = 9u;
	static char szBuf[cchBuf];
	time_t now = ::time(NULL);
	tm *ptm = localtime(&now);
	::strftime(szBuf, cchBuf, "%H:%M:%S", ptm);
	return szBuf;
}
#define REPORT() \
	::fprintf(g_fh(), "%s: [0x%08X] %s\n", timestamp(), (size_t)pRawMemory, __func__);

/**
 * The wxThread-derived class that use class-specific op new and delete
 * to record whether or not the memory has been properly released.
 */
class CThread : public wxThread
{
public:
	static void *operator new (size_t cbNeeded) {
		void *pRawMemory = ::operator new (cbNeeded);
		REPORT() // Ouput to the log file "threads.log".
		return pRawMemory;
	}
	static void operator delete (void *pRawMemory) {
		::operator delete (pRawMemory);
		REPORT()
	}
protected:
	void *Entry(void) {
		// Count to ten, but calling Destroy from the main thread might end this for-loop prematurely.
		for (size_t i = 0u; i < 10u; ++i) {
			if (this->TestDestroy()) return NULL;
			::fprintf(stderr, "%s: [0x%08X] %u\n", timestamp(), (size_t)this, i);
			wxSleep(1);
		}
		return NULL;
	}
private:
};

/**
 * The wxApp-derived class is concise.
 * Clicking on the main frame will create a new wxThread.
 * After we create several threads and let them run synchronously,
 * if we close the main frame to make the process end,
 * the wxThread objects will not be released, and this fact can
 * be seen from the log file "threads.log".
 * This resource leaks happen in both wxGTK and wxMSW.
 *
 * Please refer to wxWidgets-3.0.2/src/unix/threadpsx.cpp(1821).
 * wxWidgets does try to delete all running threads when the process ends.
 * However, the invocations of Delete() are not blocking,
 * they won't wait till the thread actually end.
 * Maybe wxThread's Delete() is where the bug occurs.
 */
class CApp : public wxApp
{
public:
	bool OnInit() {
		wxFrame *frm = new wxFrame(NULL, wxID_ANY, "MT");
		frm->Bind(wxEVT_LEFT_UP, [](wxMouseEvent& evt)->void{
			::fprintf(stderr, "%s: %s\n", timestamp(), __func__);
			CThread *thread = new CThread;
			thread->Create();
			thread->Run();
		});
		frm->Show(true);
		return this->wxApp::OnInit();
	}
};
wxDECLARE_APP(CApp);
wxIMPLEMENT_APP(CApp);
