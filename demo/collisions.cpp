#include <SFML/Graphics.hpp>
#include "../include/cpparticles.hpp"

int main()
{
    Environment *env = new Environment(800, 600);
    Particle *selectedParticle = nullptr;

    sf::RenderWindow window(sf::VideoMode(env->getWidth(), env->getHeight()), "Collision Simulation");
    window.setFramerateLimit(60);

    for (int i = 0; i < 10; i++)
    {
        env->addParticle();
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard
                    : Escape)
                    windows.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    float mouseX = event.mouseButton.x;
                    float mouseY = event.mouseButton.y;
                    selectedParticle = env->getParticle(mouseX, mouseY);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    selectedParticle = nullptr;
            }
        }
        window.clear();
        env->update();
        if (selectedParticle)
        {
            float mouseX = sf::Mouse::getPosition(window).x;
            float mouseY = sf::Mouse::getPosition(window).y;
            selectedParticle->moveTo(mouseX, mouseY);
        }

        for (int i = 0; i < env->getParticles().size(); i++)
        {
            Particle *particle = env->getParticles()[i];
            sf::CircleShape circle(particle->getSize());
            circle.setOrigin(particle->getSize(), particle->getSize());
            circle.setPosition(particle->getX(), particle->getY());
            window.draw(circle);
        }

        window.display();
    }
    return EXIT_SUCCESS;
}