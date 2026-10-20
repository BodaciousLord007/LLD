
#include <iostream>
#include <string>
using namespace std;

// Button
class IButton
{
public:
    virtual void render() = 0;
    virtual ~IButton() = default;
};

class WebButton : public IButton
{
public:
    void render() override
    {
        cout << "Rendering [Web Button]\n";
    }
};

class AndroidButton : public IButton
{
public:
    void render() override
    {
        cout << "Rendering [Android Button]\n";
    }
};

class DesktopButton : public IButton
{
public:
    void render() override
    {
        cout << "Rendering [Desktop Button]\n";
    }
};

// Text Field
class ITextField
{
public:
    virtual void render() = 0;
    virtual ~ITextField() = default;
};

class WebTextField : public ITextField
{
public:
    void render() override
    {
        cout << "Rendering [Web Text Field]\n";
    }
};

class AndroidTextField : public ITextField
{
public:
    void render() override
    {
        cout << "Rendering [Android Text Field]\n";
    }
};

class DesktopTextField : public ITextField
{
public:
    void render() override
    {
        cout << "Rendering [Desktop Text Field]\n";
    }
};

// Dialog
class IDialog
{
public:
    virtual void show() = 0;
    virtual ~IDialog() = default;
};

class WebDialog : public IDialog
{
public:
    void show() override
    {
        cout << "Showing [Web Dialog]\n";
    }
};

class AndroidDialog : public IDialog
{
public:
    void show() override
    {
        cout << "Showing [Android Dialog]\n";
    }
};

class DesktopDialog : public IDialog
{
public:
    void show() override
    {
        cout << "Showing [Desktop Dialog]\n";
    }
};

// Abstarct Factory
class IGUIFactory
{
public:
    virtual IButton *createButton() = 0;
    virtual ITextField *createTextField() = 0;
    virtual IDialog *createDialog() = 0;

    virtual ~IGUIFactory() = default;
};

// Web Factory
class WebFactory : public IGUIFactory
{
public:
    IButton *createButton() override
    {
        return new WebButton();
    }

    ITextField *createTextField() override
    {
        return new WebTextField();
    }

    IDialog *createDialog() override
    {
        return new WebDialog();
    }
};

// Android Factory
class AndroidFactory : public IGUIFactory
{
public:
    IButton *createButton() override
    {
        return new AndroidButton();
    }

    ITextField *createTextField() override
    {
        return new AndroidTextField();
    }

    IDialog *createDialog() override
    {
        return new AndroidDialog();
    }
};

// Desktop Factory
class DesktopFactory : public IGUIFactory
{
public:
    IButton *createButton() override
    {
        return new DesktopButton();
    }

    ITextField *createTextField() override
    {
        return new DesktopTextField();
    }

    IDialog *createDialog() override
    {
        return new DesktopDialog();
    }
};

// Factory Provider
class FactoryProvider
{
public:
    static IGUIFactory *getFactory(string platform)
    {
        if (platform == "web")
        {
            return new WebFactory();
        }
        else if (platform == "android")
        {
            return new AndroidFactory();
        }
        else if (platform == "desktop")
        {
            return new DesktopFactory();
        }

        return nullptr;
    }
};

// Main
int main()
{

    IGUIFactory *factory = FactoryProvider::getFactory("web");

    if (factory == nullptr)
    {
        cout << "Invalid platform!\n";
        return 1;
    }

    IButton *button = factory->createButton();
    ITextField *textField = factory->createTextField();
    IDialog *dialog = factory->createDialog();

    button->render();
    textField->render();
    dialog->show();

    // Free allocated memory
    delete button;
    delete textField;
    delete dialog;
    delete factory;

    return 0;
}

int main(){
    return 0;
}