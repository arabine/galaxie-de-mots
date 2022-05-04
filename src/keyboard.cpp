
#include "keyboard.h"
#include "letter.h"

static const float DEFAULT_SCALE = 0.4;

static const char keyboard[] = { 'a', 'z', 'e', 'r', 't', 'y','u', 'i', 'o', 'p', '\n',
                                 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '\n',
                                 '?', 'w', 'x', 'c', 'v', 'b', 'n', '<', '\n',
                               };

class Enter : public Image
{
public:
    Enter(GfxSystem &s, Keyboard::IKeyEvent &keyEvent)
        : Image(s, "letters/enter.svg", true)
        , mKeyEvent(keyEvent)
    {
        SetSvgScale(DEFAULT_SCALE);
        SetActive(true);
    }

    virtual void OnClick()
    {
//        LOG_DEBUG("Enter clicked");
        mKeyEvent.EnterPressed();
    }

private:
    Keyboard::IKeyEvent &mKeyEvent;
};

class Backspace : public Image
{
public:
    Backspace(GfxSystem &s, Keyboard::IKeyEvent &keyEvent)
        : Image(s, "letters/backspace.svg", true)
        , mKeyEvent(keyEvent)
    {
        SetSvgScale(DEFAULT_SCALE);
        SetActive(true);
    }

    virtual void OnClick()
    {
//        LOG_DEBUG("Backspace clicked");
        mKeyEvent.BackspacePressed();
    }
private:
    Keyboard::IKeyEvent &mKeyEvent;
};


Keyboard::Keyboard(GfxSystem &s, IKeyEvent &keyEvent)
    : Group(s)
    , mKeyEvent(keyEvent)
{

    // Construction des touches du clavier en mémoire
    int line = 0;

    std::list<std::shared_ptr<Entity>> obj;

    for (int i = 0; i < sizeof(keyboard); i++)
    {
        if (keyboard[i] == '\n')
        {
            // new line
            mLines.push_back(obj);
            obj.clear();
        }
        else if (keyboard[i] == '?')
        {
            auto l = std::make_shared<Enter>(GetSystem(), mKeyEvent);
            l->SetVisible(true);
            AddEntity(l);
            obj.push_back(l);
        }
        else if (keyboard[i] == '<')
        {
            auto l = std::make_shared<Backspace>(GetSystem(), mKeyEvent);
            l->SetVisible(true);
            AddEntity(l);
            obj.push_back(l);
        }
        else
        {
            char key = keyboard[i];
            auto l = std::make_shared<Letter>(GetSystem(), std::string("letters/letter_") + key + std::string(".svg"), DEFAULT_SCALE, [key, this] {
           //     LOG_DEBUG(std::string("Letter ") + key + std::string(" CLICKED"));
                mKeyEvent.KeyPressed(key);
            });
            l->SetLetter(std::toupper(key));
            l->SetVisible(true);
            l->SetActive(true);
            AddEntity(l);

            obj.push_back(l);
            mLetters.push_back(l);
        }
    }
}

Keyboard::~Keyboard()
{

}

void Keyboard::OnCreate(SDL_Renderer *renderer)
{
    Group::OnCreate(renderer);

    // Les objects sont créés avec un renderer et une texture, on peut donc les positionner à l'écran
    // ligne par ligne

    int y = 0;
    int x = 0;
    int x_max = 0;
    int y_max = 0;

    for (int i = 0; i < mLines.size(); i++)
    {
        x = 0;
        y_max = 0;

        // Première boucle pour déterminer la largeur totale de tous les objets
        // Ainsi que la hauteur max de la ligne
        for (auto &l : mLines[i])
        {
            x += l->GetRect().w;
            if (l->GetRect().h > y_max)
            {
                y_max = l->GetRect().h;
            }

            if (x > x_max)
            {
                x_max = x;
            }
        }

        std::cout << "XMAX: " << x_max << std::endl;

        int offset = (GetSystem().GetScreenW() - x_max) / mLines[i].size();

        // Deuxième boucle pour placer les objets
        int start_x = offset;
        for (auto &l : mLines[i])
        {
            l->SetPos(start_x, y);

            start_x += offset + l->GetRect().w;
        }


        // new line
        y += y_max + 10;

    }
    SetOrigin(0, GetSystem().GetScreenH() - y);
}

void Keyboard::Initialize()
{
    mCodage.clear();
    for (auto &c : mLetters)
    {
        c->SetBackgroundColor("#585860");
        c->Rebuild();
    }
}

void Keyboard::ProcessEvent(const SDL_Event &event)
{
    Group::ProcessEvent(event);
    //User presses a key
    if( event.type == SDL_KEYDOWN )
    {
        //Select surfaces based on key press
        SDL_Keycode k = event.key.keysym.sym;
        if ((k >= SDLK_a) && (k <= SDLK_z))
        {
            // key offset
            int offset = k - SDLK_a;
            // transform to character code
            char c = 'a' + offset;
            mKeyEvent.KeyPressed(c);
        }
        else if (k == SDLK_RETURN)
        {
            mKeyEvent.EnterPressed();
        }
        else if (k == SDLK_BACKSPACE)
        {
            mKeyEvent.BackspacePressed();
        }
    }
}

void Keyboard::SetUsedLetters(const std::string &word, std::string codage)
{
    // D'abord on met à jour le status des lettres jouées
    for (int i = 0; i < word.size(); i++)
    {
        char k = word[i];
        char c = codage[i];

        if (mCodage.count(k))
        {
            char cLast = mCodage[k];
            // La lettre a déjà été jouée
            if (c > cLast)
            {
                mCodage[k] = c;
            }
        }
        else
        {
            // Lettre jamais jouée
            mCodage[k] = c;
        }
    }

    // Ensuite on met à jour la couleur de chaque lettre du clavier
    for (auto &c : mLetters)
    {
        if (mCodage.count(c->GetLetter()))
        {
            char code = mCodage[c->GetLetter()];

            if (code == '0')
            {
                c->SetBackgroundColor("#202020");
                c->Rebuild();
            }
            else if (code == '1')
            {
                c->SetBackgroundColor("#D3952A");
                c->Rebuild();
            }
            else if (code == '2')
            {
                c->SetBackgroundColor("#3EAA42");
                c->Rebuild();
            }
        }
    }
}

