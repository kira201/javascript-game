#include "AppDelegate.h"

#include "SimpleAudioEngine.h"
#include "jsb_cocos2dx_auto.hpp"
#include "jsb_cocos2dx_ui_auto.hpp"
#include "jsb_cocos2dx_studio_auto.hpp"
#include "jsb_cocos2dx_builder_auto.hpp"
#include "jsb_cocos2dx_spine_auto.hpp"
#include "jsb_cocos2dx_extension_auto.hpp"
#include "ui/jsb_cocos2dx_ui_manual.h"
#include "cocostudio/jsb_cocos2dx_studio_manual.h"
#include "cocosbuilder/js_bindings_ccbreader.h"
#include "spine/jsb_cocos2dx_spine_manual.h"
#include "extension/jsb_cocos2dx_extension_manual.h"
#include "localstorage/js_bindings_system_registration.h"
#include "chipmunk/js_bindings_chipmunk_registration.h"
#include "jsb_opengl_registration.h"
#include "network/XMLHTTPRequest.h"
#include "network/jsb_websocket.h"
#include "network/jsb_socketio.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/CCJavascriptJavaBridge.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/ios/JavaScriptObjCBridge.h"
#endif
#include "cocostudio\CCArmature.h"

#include "ui/UIVideoPlayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocostudio;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    ScriptEngineManager::destroyInstance();
}

int appShaderArgumentOfFloat(Node* node, Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4) {
	auto qq = dynamic_cast<Sprite*>(node);
	if(qq != nullptr) {
		node->getGLProgramState()->setUniformVec3("v1", v1);
		node->getGLProgramState()->setUniformVec3("v2", v2);
		node->getGLProgramState()->setUniformVec3("v3", v3);
		node->getGLProgramState()->setUniformVec3("v4", v4);
		//return 0;
	}
	if(node->getChildrenCount()> 0){
		for(auto& child: node->getChildren()){
			appShaderArgumentOfFloat(child, v1, v2, v3, v4);
		}
	}
	
	return 0;
}

bool jsb_applyShaderArgument(JSContext *cx, uint32_t argc, JS::Value *vp) {
	bool ok = true;
	jsval *argv = JS_ARGV(cx, vp);
	//Node * node = JSVAL_TO_INT(argv[0]);
	
	JSObject *obj = JSVAL_TO_OBJECT(argv[0]);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Node* node = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( node, cx, false, "argument1 : Invalid Native Object");


	//std::string name;
	//ok &= jsval_to_std_string(cx, argv[1], &name);
	//JSB_PRECONDITION2(ok, cx, false, "argument2 : uniform name");
	//ok &= JSVAL_IS_NUMBER(argv[1]);
	//ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[1]), v1);
	//JSB_PRECONDITION2(ok, cx, false, "argument3 : range 0.0-1.0");

	Vec3 v1, v2, v3, v4;
	//ok &= jsval_to_cccolor4f(cx, argv[1], &v1);
	//ok &= jsval_to_cccolor4f(cx, argv[2], &v2);
	//ok &= jsval_to_cccolor4f(cx, argv[3], &v3);
	jsval_to_vector3(cx, argv[1], &v1);
	jsval_to_vector3(cx, argv[2], &v2);
	jsval_to_vector3(cx, argv[3], &v3);
	jsval_to_vector3(cx, argv[4], &v4);

	jsval ret = int32_to_jsval(cx, appShaderArgumentOfFloat(node, v1, v2, v3, v4));
	JS_SET_RVAL(cx, vp,  ret); 
	return true;
}

//VideoPlayer
int videoPlayerArgumentOfString(Node* node, std::string name) {
	if(node != nullptr) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	
		experimental::ui::VideoPlayer* videoPlayer = experimental::ui::VideoPlayer::create();
		videoPlayer->setFileName(name);
		node->addChild(videoPlayer,1001);
		videoPlayer->setContentSize(Size(100 ,100));
	    videoPlayer->setKeepAspectRatioEnabled(true);
	    videoPlayer->setFullScreenEnabled(true);
	    videoPlayer->play();
		videoPlayer->addEventListener([&,videoPlayer,node](Ref *pSender, experimental::ui::VideoPlayer::EventType type){
			switch(type)
			{
				case experimental::ui::VideoPlayer::EventType::COMPLETED:
					videoPlayer->setVisible(false);
					node->removeChildByTag(1055);
					break;
			}
		});
#endif
	}
	
	return 0;
}
bool jsb_videoPlayer(JSContext *cx, uint32_t argc, JS::Value *vp) {
	bool ok = true;
	jsval *argv = JS_ARGV(cx, vp);
	//Node * node = JSVAL_TO_INT(argv[0]);
	
	JSObject *obj = JSVAL_TO_OBJECT(argv[0]);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::Node* node = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( node, cx, false, "argument1 : Invalid Native Object");


	std::string name;
	ok &= jsval_to_std_string(cx, argv[1], &name);
	JSB_PRECONDITION2(ok, cx, false, "argument2 : playerVideo name");
	//ok &= JSVAL_IS_NUMBER(argv[1]);
	//ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[1]), v1);
	//JSB_PRECONDITION2(ok, cx, false, "argument3 : range 0.0-1.0");

	jsval ret = int32_to_jsval(cx, videoPlayerArgumentOfString(node, name));
	JS_SET_RVAL(cx, vp,  ret); 
	return true;
}

void register_jsb_gg(JSContext *cx, JSObject *obj) {
	JS_DefineFunction(cx, obj, "gg_applyShaderUniform", jsb_applyShaderArgument, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE);
	JS_DefineFunction(cx, obj, "gg_videoPlayer", jsb_videoPlayer, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::createWithRect("lomtest", Rect(0,0,900,640));
		director->setOpenGLView(glview);
	}

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_all_cocos2dx_extension);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
    sc->addRegisterCallback(jsb_register_chipmunk);
    sc->addRegisterCallback(jsb_register_system);
    sc->addRegisterCallback(JSB_register_opengl);
    
    sc->addRegisterCallback(register_all_cocos2dx_builder);
    sc->addRegisterCallback(register_CCBuilderReader);
    
	sc->addRegisterCallback(register_all_cocos2dx_ui);
	sc->addRegisterCallback(register_all_cocos2dx_ui_manual);
	sc->addRegisterCallback(register_all_cocos2dx_studio);
	sc->addRegisterCallback(register_all_cocos2dx_studio_manual);
    
    sc->addRegisterCallback(register_all_cocos2dx_spine);
    sc->addRegisterCallback(register_all_cocos2dx_spine_manual);
    
    sc->addRegisterCallback(MinXmlHttpRequest::_js_register);
    sc->addRegisterCallback(register_jsb_websocket);
	sc->addRegisterCallback(register_jsb_socketio);
    
	sc->addRegisterCallback(register_jsb_gg);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sc->addRegisterCallback(JavascriptJavaBridge::_js_register);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    sc->addRegisterCallback(JavaScriptObjCBridge::_js_register);
#endif
    sc->start();    
    sc->runScript("script/jsb_boot.js");
    ScriptEngineProtocol *engine = ScriptingCore::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(engine);
	ScriptingCore::getInstance()->runScript("main.js");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    auto director = Director::getInstance();
    director->stopAnimation();
    director->getEventDispatcher()->dispatchCustomEvent("game_on_hide");
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();    
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    auto director = Director::getInstance();
    director->startAnimation();
    director->getEventDispatcher()->dispatchCustomEvent("game_on_show");
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
