
#include <iostream>
#include <string>
using namespace std;

// Processing Strategy
class IProcessingStrategy
{
public:
    virtual void process(string report) = 0;
    virtual ~IProcessingStrategy() = default;
};

class SimpleProcessing : public IProcessingStrategy
{
public:
    void process(string report) override
    {
        cout << "Simple Processing:\n";
        cout << report << "\n";
    }
};

class AdvancedProcessing : public IProcessingStrategy
{
public:
    void process(string report) override
    {
        cout << "Advanced Processing:\n";
        cout << report << "\n";
    }
};

// Report Config
class ReportConfig
{
private:
    bool charts;
    bool summary;
    bool footnotes;

public:
    ReportConfig(bool charts, bool summary, bool footnotes)
        : charts(charts), summary(summary), footnotes(footnotes) {}

    bool hasCharts() const
    {
        return charts;
    }

    bool hasSummary() const
    {
        return summary;
    }

    bool hasFootnotes() const
    {
        return footnotes;
    }
};

// Report Builder
class reportBuilder
{
private:
    bool chart = false;
    bool summary = false;
    bool footNote = false;

public:
    reportBuilder &addChart()
    {
        chart = true;
        return *this;
    }

    reportBuilder &addSummary()
    {
        summary = true;
        return *this;
    }

    reportBuilder &addFootNote()
    {
        footNote = true;
        return *this;
    }

    ReportConfig *build()
    {
        return new ReportConfig(chart, summary, footNote);
    }
};

// Report Generator
class IReport
{
protected:
    IProcessingStrategy *strategy;
    ReportConfig *config;

    virtual void loadData() = 0;
    virtual void processData() = 0;
    virtual void renderSection() = 0;
    virtual void exportData() = 0;

public:
    IReport(IProcessingStrategy *strategy, ReportConfig *config)
        : strategy(strategy), config(config) {}

    virtual ~IReport() = default;

    void generate()
    {
        loadData();
        processData();
        renderSection();
        exportData();
    }
};

// Client A Report
class ClientAReport : public IReport
{
protected:
    void loadData() override
    {
        cout << "Loading Client A Data\n";
    }

    void processData() override
    {
        strategy->process("Client A Data");
    }

    void renderSection() override
    {
        if (config->hasCharts())
        {
            cout << "Rendering Client A Chart\n";
        }
        if (config->hasSummary())
        {
            cout << "Rendering Client A Summary\n";
        }
        if (config->hasFootnotes())
        {
            cout << "Rendering Client A Footnotes\n";
        }
    }

    void exportData() override
    {
        cout << "Exporting Client A Report\n";
    }

public:
    ClientAReport(ReportConfig *config, IProcessingStrategy *strategy)
        : IReport(strategy, config) {}
};

// Client B Report
class ClientBReport : public IReport
{
protected:
    void loadData() override
    {
        cout << "Loading Client B Data\n";
    }

    void processData() override
    {
        strategy->process("Client B Data");
    }

    void renderSection() override
    {
        if (config->hasCharts())
        {
            cout << "Rendering Client B Chart\n";
        }
        if (config->hasSummary())
        {
            cout << "Rendering Client B Summary\n";
        }
        if (config->hasFootnotes())
        {
            cout << "Rendering Client B Footnotes\n";
        }
    }

    void exportData() override
    {
        cout << "Exporting Client B Report\n";
    }

public:
    ClientBReport(ReportConfig *config, IProcessingStrategy *strategy)
        : IReport(strategy, config) {}
};

int main()
{
    ReportConfig *config = reportBuilder()
                               .addChart()
                               .addSummary()
                               .build();

    IProcessingStrategy *strategy = new SimpleProcessing();

    IReport *report = new ClientAReport(config, strategy);

    report->generate();

    delete report;
    delete strategy;
    delete config;

    return 0;
}
