
#include <iostream>
#include <stack>
#include <list>
#include <string>
using namespace std;

// Editor
class Editor
{
private:
    string content;

public:
    void insert(int pos, string text)
    {
        if (pos < 0 || pos > (int)content.size())
            throw out_of_range("Invalid position");

        content.insert(pos, text);
        cout << "Inserting " << text << " at " << pos << "\n";
    }

    void deleteText(int pos, int len)
    {
        if (pos < 0 || len < 0 ||
            pos > (int)content.size() ||
            len > (int)content.size() - pos)
            throw out_of_range("Invalid delete range");

        content.erase(pos, len);

        cout << "Deleting from " << pos
             << " to " << pos + len - 1 << "\n";
    }

    void format(int start, int end)
    {
        if (start < 0 || end < start ||
            end > (int)content.size())
            throw out_of_range("Invalid format range");

        for (int i = start; i < end; i++)
        {
            content[i] = toupper(
                static_cast<unsigned char>(content[i]));
        }

        cout << "Formatting from " << start
             << " to " << end - 1 << "\n";
    }

    string getText(int pos, int len)
    {
        if (pos < 0 || len < 0 ||
            pos > (int)content.size() ||
            len > (int)content.size() - pos)
            throw out_of_range("Invalid text range");

        return content.substr(pos, len);
    }

    void restoreFormat(int pos, string text)
    {
        if (pos < 0 ||
            pos > (int)content.size() ||
            text.size() > content.size() - pos)
            throw out_of_range("Invalid restore range");

        content.replace(pos, text.size(), text);

        cout << "Restoring original format of "
             << text << " at " << pos << "\n";
    }

    void show()
    {
        cout << "Editor Content: " << content << "\n";
    }
};

// Command
class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

// InsertTextCommand
class InsertTextCommand : public Command
{
private:
    Editor *editor;
    int position;
    string text;

public:
    InsertTextCommand(Editor *editor, int position, string text)
        : editor(editor), position(position), text(text) {}

    void execute() override
    {
        editor->insert(position, text);
    }

    void undo() override
    {
        editor->deleteText(position, text.size());
    }
};

// DeleteTextCommand
class DeleteTextCommand : public Command
{
private:
    Editor *editor;
    int position;
    int length;
    string deletedText;

public:
    DeleteTextCommand(Editor *editor, int position, int length)
        : editor(editor), position(position), length(length) {}

    void execute() override
    {
        deletedText = editor->getText(position, length);
        editor->deleteText(position, length);
    }

    void undo() override
    {
        editor->insert(position, deletedText);
    }
};

// FormatCommand
class FormatCommand : public Command
{
private:
    Editor *editor;
    int rangeStart;
    int rangeEnd;
    string previousText;

public:
    FormatCommand(Editor *editor, int start, int end)
        : editor(editor), rangeStart(start), rangeEnd(end) {}

    void execute() override
    {
        previousText = editor->getText(
            rangeStart, rangeEnd - rangeStart);

        editor->format(rangeStart, rangeEnd);
    }

    void undo() override
    {
        editor->restoreFormat(rangeStart, previousText);
    }
};

// CommandHistory
class CommandHistory
{
private:
    stack<Command *> history;

public:
    void push(Command *cmd)
    {
        history.push(cmd);
    }

    Command *pop()
    {
        if (history.empty())
        {
            cout << "No command to undo\n";
            return nullptr;
        }

        Command *cmd = history.top();
        history.pop();

        return cmd;
    }

    void undo()
    {
        Command *cmd = pop();

        if (cmd != nullptr)
        {
            cmd->undo();
        }
    }
};

// Macro
class Macro
{
private:
    list<Command *> commandList;

public:
    void record(Command *cmd)
    {
        commandList.push_back(cmd);
    }

    void play()
    {
        cout << "Playing Macro:\n";

        for (auto cmd : commandList)
        {
            cmd->execute();
        }

        cout << "\n";
    }
};

// Main
int main()
{
    Editor editor;
    CommandHistory history;

    InsertTextCommand cmd1(&editor, 0, "Hello");
    InsertTextCommand cmd2(&editor, 5, " World");
    DeleteTextCommand cmd3(&editor, 5, 6);
    FormatCommand cmd4(&editor, 0, 5);

    // Execute commands
    cout << "Executing Commands:\n";

    cmd1.execute();
    history.push(&cmd1);

    cmd2.execute();
    history.push(&cmd2);

    cmd3.execute();
    history.push(&cmd3);

    cmd4.execute();
    history.push(&cmd4);

    editor.show();

    // Undo commands
    cout << "\nUndo Commands:\n";

    history.undo();
    editor.show();

    history.undo();
    editor.show();

    history.undo();
    editor.show();

    history.undo();
    editor.show();

    history.undo();

    // Macro
    cout << "\nMacro Demonstration:\n";

    InsertTextCommand m1(&editor, 0, "Hello");
    InsertTextCommand m2(&editor, 5, " World");
    FormatCommand m3(&editor, 0, 5);

    Macro macro;

    macro.record(&m1);
    macro.record(&m2);
    macro.record(&m3);

    macro.play();
    editor.show();

    return 0;
}
