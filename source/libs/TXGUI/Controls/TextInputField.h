#ifndef iSeer_TextInputField_h
#define iSeer_TextInputField_h

#include "cocos2d.h"

USING_NS_CC;

namespace TXGUI
{
	class TextInputField: public CCTextFieldTTF, public CCTextFieldDelegate, public CCTouchDelegate
	{
	private:
		// �����ʼλ��
		CCPoint m_beginPos;

		// ��꾫��
		CCSprite *m_pCursorSprite;

		// ��궯��
		CCAction *m_pCursorAction;

		// �������
		CCPoint m_cursorPos;

		// ���������
		std::string m_strInputText;

		// �Ƿ���������
		bool m_bIsPassword;

		// ��ʾ����
		std::string m_strShowText;

		// �Ƿ��Ѿ�schedule
		bool m_bIsScheduled;

		// ��������
		int m_iLengthLimit;

	protected:
		// CCTextFieldTTF
		virtual const char *getContentText();

	public:
		TextInputField();
		~TextInputField();

		// static
		static TextInputField* textFieldWithPlaceHolder(const char *placeholder, CCSize dimensions, 
			CCTextAlignment alignment, const char *fontName, float fontSize);
		static TextInputField* textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);

		// CCTextFieldTTF
		virtual void onEnter();
		virtual void onExit();

		// ��ʼ����꾫��
		void initCursorSprite(int nHeight);

		// CCTextFieldTTF
		virtual bool attachWithIME();
		virtual bool detachWithIME();

		// CCTextFieldDelegate
		virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);
		virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
		virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
		virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);

        virtual void resetInputText(const char *label);
		// CCLayer Touch
		bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

		// �����Ƿ���������
		void setIsPassword(bool value);

		// ����ʾ�ַ���ת��Ϊ������ʽ
		void ChangeToPassword(float dt);

		// ������������
		void setLengthLimit(int value);

		// �õ�dimensions
		CCSize getDimensions();

		// ��ȡ���������
		virtual const char *getString();

		// ������������
		virtual void clearString();

	private:
		// �ж��Ƿ�����TextField��
		bool isInTextField(CCTouch *pTouch);
		// �õ�TextField����
		CCRect getRect();
	};
}


#endif
