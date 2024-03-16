#include <iostream>
#include <array>
#include <thread>

#include <Helper.h>
#include <SFML/Window/Event.hpp>
#include "../include/window.h"
#include "../include/userInterface.h"
#include "../include/entity.h"
#include "../include/fightScreen.h"
//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "../env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/// This class is used to test that the memory leak checks work as expected even when using a GUI
class SomeClass {
public:
    explicit SomeClass(int) {}
};

SomeClass *getC() {
    return new SomeClass{2};
}
//////////////////////////////////////////////////////////////////////


int main() {
    ////////////////////////////////////////////////////////////////////////
    /// NOTE: this function call is needed for environment-specific fixes //
    init_threads();                                                       //
    ////////////////////////////////////////////////////////////////////////
    ///
    std::cout << "Hello, world!\n";
    std::array<int, 100> v{};
    int nr;
    std::cout << "Introduceți nr: ";
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
    std::cin >> nr;
    /////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < nr; ++i) {
        std::cout << "v[" << i << "] = ";
        std::cin >> v[i];
    }
    std::cout << "\n\n";
    std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    for(int i = 0; i < nr; ++i) {
        std::cout << "- " << v[i] << "\n";
    }
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
    ///                Exemplu de utilizare cod generat                     ///
    ///////////////////////////////////////////////////////////////////////////
    Helper helper;
    helper.help();
    ///////////////////////////////////////////////////////////////////////////

    SomeClass *c = getC();
    std::cout << c << "\n";
    delete c;
    Label::initFont();
    GameWindow window("Dungeons", (int)sf::VideoMode::getDesktopMode().width, (int)sf::VideoMode::getDesktopMode().height);
    bool running = true;
    Panel testPanel;
    testPanel.toggleVisibility();
    Entity testEntity;
    std::cout << testEntity;
    while(window.getWindow().isOpen() && running) {
        sf::Event event{};
        while(window.getWindow().pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                running = false;
                break;
            }
            if(event.type== sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    running = false;
                    break;
                }
            }

        }
        window.getWindow().clear();
        FightScreen fightScreen;
        fightScreen.draw(window.getWindow());
//        sf::Sprite sprite;
//        sprite.setTexture(*GameWindow::getTexture("test"));
//        sprite.setScale(500.0f,500.0f);
//        window.getWindow().draw(sprite);
//        sf::Text text;
//        sf::Font font;
//        font.loadFromFile("../res/fonts/8bitOperatorPlus8-Regular.ttf");
//        text.setFont(font);
//        text.setCharacterSize(12);
//        text.setLetterSpacing(0.5f);
//        text.setString("test text\npentru sfml");
//        window.getWindow().draw(text);
//        Label text;
//        text.setText("test text cu wrapping prin sfml", 12);
//        text.draw(window.getWindow());
//        int x = sf::Mouse::getPosition().x;
//        int y = sf::Mouse::getPosition().y;
//        std::cout<<x<<' '<<y<<'\n';
//        std::cout<<sf::VideoMode::getDesktopMode().width<<", "<<sf::VideoMode::getDesktopMode().height<<'\n';

//        testPanel.addComponent(Label("Test text pentru Panel class"));
//        testPanel.addComponent(Component());
//        testPanel.getComponent(2).getRectangleShape().setTexture(GameWindow::getTexture("test"));
//        testPanel.addButton(Button());
//        if(testPanel.getButton(1).isPressed())std::cout<<"Pressed\n";
//        testPanel.draw(window.getWindow());
        window.getWindow().display();
    }
//    std::cout << "Test getTexture address: " << &window.getTexture("Noone") << "\n";
//    sf::RenderWindow window;
//    ///////////////////////////////////////////////////////////////////////////
//    /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
//    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
//    ///////////////////////////////////////////////////////////////////////////
//    //
//    ///////////////////////////////////////////////////////////////////////////
//    /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
//    /// This is needed so we do not burn the GPU                            ///
//    window.setVerticalSyncEnabled(true);                            ///
//    /// window.setFramerateLimit(60);                                       ///
//    ///////////////////////////////////////////////////////////////////////////
//
//    while(window.isOpen()) {
//        bool shouldExit = false;
//        sf::Event e{};
//        while(window.pollEvent(e)) {
//            switch(e.type) {
//            case sf::Event::Closed:
//                window.close();
//                break;
//            case sf::Event::Resized:
//                std::cout << "New width: " << window.getSize().x << '\n'
//                          << "New height: " << window.getSize().y << '\n';
//                break;
//            case sf::Event::KeyPressed:
//                std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
//                if(e.key.code == sf::Keyboard::Escape)
//                    shouldExit = true;
//                break;
//            default:
//                break;
//            }
//        }
//        if(shouldExit) {
//            window.close();
//            break;
//        }
//        using namespace std::chrono_literals;
//        std::this_thread::sleep_for(300ms);
//
//        window.clear();
//        window.display();
//    }
    return 0;
}
