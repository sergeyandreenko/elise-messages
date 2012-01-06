/*
Elise Messages Plugin for Miranda IM

*/

class Elise;

#ifndef ELISE_H
#define ELISE_H

#include <QtCore>
#include <QtGui>
#include <QWebView>
#include <QtWebKit>
#include <QWinWidget>

#include "main.h"
#include "m_ieview.h"
#include "template.h"
#include "HTMLBuilder.h"


class Elise {
private:
        static Elise* list;
        static CRITICAL_SECTION mutex;
        //static HWND hElise;
        static bool isInited;
        HWND		hwnd;
        HWND 		parent;
        Elise		*prev, *next;
        //RECT		rcClient;
        int         height;
        int         width;
        QWinWidget*      mainWnd;
        QWebView*        webView;
        HTMLBuilder      builder;
protected:
        //void			navigate(const char *);
        //void			navigate(const wchar_t *);
public:
        Elise(HWND parent, int x, int y, int cx, int cy);
        ~Elise();
        HWND			getHWND();
        static Elise* 	get(HWND);
        void            setWindowPos(int x, int y, int cx, int cy);
        void            scrollToBottom();
        void            appendEvent(IEVIEWEVENT * event);
        void            appendEventOld(IEVIEWEVENT * event);
        void            clear(IEVIEWEVENT * event);
        int             getSelection(IEVIEWEVENT * event);
        void            saveDocument();

        static int      InitEliseMessages(void);
        static void     ReleaseEliseMessages(void);
};


#endif // ELISE_H
