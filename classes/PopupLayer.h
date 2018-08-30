#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class PopupLayer : public LayerColor{
public:
	PopupLayer();
	~PopupLayer();
	
	virtual bool init();
	CREATE_FUNC(PopupLayer);
	static PopupLayer* create(const char* backgroundImage,Size dialogSize);

	//touch�¼����� �������´���
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);

	//����
	void setTitle(const char* title, int fontsize = 20);
	//�ı�
	void setContentText(const char* text, int fontsize = 20, int padding = 50, int paddintTop = 100);
	//����button�ص��¼�
	void setCallbackFunc(Ref* target, SEL_CallFuncN callfun);
	//���button
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag, Point pos);

	virtual void onEnter();
	virtual void onExit();

	void backgroundFinish();

private:
	
	void buttonCallBack(Ref* pSender);

	// �����������ߵĿհ���
	int m_contentPadding;
	int m_contentPaddingTop;

	Size m_dialogContentSize;

	Ref* m_callbackListener;
	SEL_CallFuncN m_callback;

	//set and get
	CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
	CC_SYNTHESIZE_RETAIN(Sprite*, m__sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m__s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltContentText, LabelContentText);
};