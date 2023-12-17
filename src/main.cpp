
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <iostream>
#include "motus-gui.h"
#include "home-scene.h"
#include "scenes.h"
#include "application.h"
#include "thread_queue.h"

class EventStub : public Motus::IGameEvent
{
public:
    virtual void AppendLetter(char c)
    {
    }
    virtual void RemoveLast()
    {
    }
    virtual void Validate(const std::string &codage)
    {
    }
    virtual void Message(const std::string &message)
    {
    }
    virtual void NewGame()
    {
    }
};

class AppStub : public IApplication
{
public:
    virtual std::string GetRandomWord(int nbLetters) override
    {
        return "GRUME";
    }
    virtual bool IsWordExists(const std::string &word) override
    {
        return true;
    }
    virtual bool GetDefinition(const std::string &mot, std::string &sens, std::string &categorie) override
    {
        return true;
    }
};

static EventStub eventStub;
static AppStub appStub;

static Motus motus(eventStub, appStub);

static void UnitTest()
{
    motus.Initialize();
    motus.SetCurrentWord("GRUME");

    std::string code = motus.TestWord("MAMAN");

    std::cout << "Resultat: " << code << std::endl;

    if (code == "10000")
    {
        std::cout << "SUCCESS\n"
                  << std::endl;
    }
    else
    {
        std::cout << "BOUH :( :( :(\n"
                  << std::endl;
    }
}

#include <jni.h>

static ThreadQueue<std::string> gQueue;

extern "C"
{
    void Java_eu_d8s_galaxie_GalaxieActivity_printFromJava(JNIEnv *env, jobject obj, jstring txt)
    {
        (void)(env);
        (void)(obj);

        std::string txtStr = env->GetStringUTFChars(txt, nullptr);

        std::cout << "Got infos from device: " << txt << std::endl;
        gQueue.Push(txtStr);
    }
}

extern "C" int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    //    UnitTest();
    //    return 0;

    GfxEngine mGfx;
    Scene::MessageQueue msg;

    Application app;

    if (mGfx.Initialize("Galaxie de mots"))
    {
        std::cout << "[INIT] Success" << std::endl;

        bool loop = true;
        auto motusScene = std::make_shared<MotusGui>(mGfx, app);
        mGfx.AddScene(motusScene, SCENE_MOTUS);

        auto homeScene = std::make_shared<HomeScene>(mGfx);
        mGfx.AddScene(homeScene, SCENE_HOME);

        mGfx.SwitchSceneTo(SCENE_HOME); // First scene
        mGfx.Warmup();

        motusScene->Initialize();

        std::string messageTxt;
        while (loop)
        {
            if (gQueue.TryPop(messageTxt))
            {
                msg.push_back(std::make_pair<std::string, Value>("debug", messageTxt));
                homeScene->OnMessage(msg);
            }

            if (mGfx.Process() == SCENE_EXIT)
            {
                loop = false;
            }
        }
    }
    else
    {
        std::cout << "[INIT] ERROR" << std::endl;
    }

    std::cout << "[INIT] Galaxie exit" << std::endl;

    return 0;
}
