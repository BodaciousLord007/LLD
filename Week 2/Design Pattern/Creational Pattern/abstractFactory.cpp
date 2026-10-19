#include <iostream>
using namespace std;

class Button
{
public:
    virtual ~Button() = default;
    virtual void render() = 0;
};

class LightButton : public Button
{
public:
    void render() override
    {
        cout << "Rendering Light Button\n";
    }
};

class DarkButton : public Button
{
public:
    void render() override
    {
        cout << "Rendering Dark Button\n";
    }
};

class Checkbox
{
public:
    virtual ~Checkbox() = default;
    virtual void render() = 0;
};

class LightCheckbox : public Checkbox
{
public:
    void render() override
    {
        cout << "Rendering Light Checkbox\n";
    }
};

class DarkCheckbox : public Checkbox
{
public:
    void render() override
    {
        cout << "Rendering Dark Checkbox\n";
    }
};

class UIFactory
{
public:
    virtual ~UIFactory() = default;
    virtual Button *createButton() = 0;
    virtual Checkbox *createCheckbox() = 0;
};

class LightThemeFactory : public UIFactory
{
public:
    Button *createButton() override
    {
        return new LightButton();
    }

    Checkbox *createCheckbox() override
    {
        return new LightCheckbox();
    }
};

class DarkThemeFactory : public UIFactory
{
public:
    Button *createButton() override
    {
        return new DarkButton();
    }

    Checkbox *createCheckbox() override
    {
        return new DarkCheckbox();
    }
};
int main()
{
    Button *b;
    Checkbox *c;

    // Testing Light
    LightThemeFactory *l = new LightThemeFactory();

    b = l->createButton();
    b->render();

    c = l->createCheckbox();
    c->render();

    delete b;
    delete c;
    delete l;

    // Testing Dark
    DarkThemeFactory *d = new DarkThemeFactory();

    b = d->createButton();
    b->render();

    c = d->createCheckbox();
    c->render();

    delete b;
    delete c;
    delete d;

    return 0;
}