/*
Elise Messages Plugin for Miranda IM

*/

#include "main.h"
#include "Elise.h"
#include "utils.h"
#include "options.h"
#include "services.h"
#include <QLineEdit>

Elise* Elise::list = NULL;
CRITICAL_SECTION Elise::mutex;
bool Elise::isInited = false;

// ��� ����� ���� ������� ���, �.�. ����� ���
// ���� �������� ������������ miranda.exe
QString skinPath("Skins/IEView/testSkin/myskin.ivt");
QUrl skinDir = QUrl(QDir::currentPath() + "/" + skinPath);

Elise::Elise(HWND parent, int x, int y, int cx, int cy) {

    this->parent = parent;
    prev = next = NULL;
    hwnd = NULL;

    //rcClient.left = x;
    //rcClient.top = y;
    //rcClient.right = x + cx;
    //rcClient.bottom = y + cy;
    height = cy;
    width = cx;

    mainWnd = new QWinWidget(parent);
    webView = new QWebView(mainWnd);

    builder.initDoc();

    // ����� ���� �����, ����� ����������
    //webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    //QObject::connect(webView, SIGNAL(linkClicked(QUrl)), qApp, SLOT(linkClicked (QUrl)),
    //                 Qt::DirectConnection);

    hwnd = mainWnd->winId();

    webView->setHtml(builder.getDoc(), skinDir);
    //webView->settings()->JavaEnabled = QWebSettings::JavascriptEnabled;
    webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);

    mainWnd->show();

    EnterCriticalSection(&mutex);
    next = list;
    if (next != NULL) {
        next->prev = this;
    }
    list = this;
    LeaveCriticalSection(&mutex);
}

Elise::~Elise() {
	EnterCriticalSection(&mutex);
	if (list == this) {
		list = next;
	} else if (prev!=NULL) {
		prev->next = next;
	}
	if (next != NULL) {
		next->prev = prev;
	}
	prev = NULL;
	next = NULL;
	LeaveCriticalSection(&mutex);

	webView->~QWebView();
	mainWnd->~QWinWidget();
}

HWND Elise::getHWND() {
	return hwnd;
}

Elise* Elise::get(HWND hwnd) {
    Elise* ptr;
    if (list == NULL) return NULL;
    EnterCriticalSection(&mutex);
    for (ptr = list; ptr !=NULL; ptr=ptr->next) {
        if (ptr->hwnd == hwnd) {
            break;
        }
    }
    LeaveCriticalSection(&mutex);
    return ptr;
}

void Elise::setWindowPos(int x, int y, int cx, int cy) {
    //rcClient.left = x;
    //rcClient.top = y;
    //rcClient.right = cx;
    //rcClient.bottom = cy;

    height = cy;
    width = cx;

    SetWindowPos(hwnd, HWND_TOP, x, y, cx, cy, 0);
    webView->resize(width, height);
}

void Elise::scrollToBottom() {
    webView->page()->mainFrame()->scroll(0, webView->page()->mainFrame()->scrollBarMaximum(Qt::Vertical));
}

void Elise::appendEvent(IEVIEWEVENT* event) {
    if (event->eventData == NULL) {return; }
    builder.appendEventNew(this, event);

    webView->setHtml(builder.getDoc(), skinDir);
    //webView->reload();
}

void Elise::appendEventOld(IEVIEWEVENT* event) {
    builder.appendEventOld(this, event);

    webView->setHtml(builder.getDoc(), skinDir);
    //webView->reload();
}

void Elise::clear(IEVIEWEVENT* event) {

}

int Elise::getSelection(IEVIEWEVENT* event) {
    return 0;
}

void Elise::saveDocument() {

}

int Elise::InitEliseMessages(void)
{
	if (isInited) return 0;
	isInited = true;
	InitializeCriticalSection(&mutex);

	//Utils::hookEvent_Ex(ME_OPT_INITIALISE, EliseOptInit);
	//Utils::hookEvent_Ex(ME_SYSTEM_MODULESLOADED, Utils::ModulesLoaded);
	//Utils::hookEvent_Ex(ME_SYSTEM_PRESHUTDOWN, PreShutdown);

	Utils::createServiceFunction_Ex(MS_IEVIEW_WINDOW, (MIRANDASERVICE)HandleEliseWindow);
	Utils::createServiceFunction_Ex(MS_IEVIEW_EVENT, (MIRANDASERVICE)HandleEliseEvent);
	//utils::createServiceFunction_Ex(MS_IEVIEW_EVENT,(MIRANDASERVICE) HandleIENavigate);
	//hHookOptionsChanged = CreateHookableEvent(ME_IEVIEW_OPTIONSCHANGED);

	TemplateMap::LoadTemplate(skinPath);

	//QMessageBox msgBox;
	//msgBox.setText(templateMap["<!--HTMLStart-->"] + templateMap["<!--MessageIn-->"]);
	//msgBox.exec();

	return 0;
}

void Elise::ReleaseEliseMessages() {
	EnterCriticalSection(&mutex);
	while (list != NULL) {
		delete list;
	}
	LeaveCriticalSection(&mutex);
	DeleteCriticalSection(&mutex);
}
