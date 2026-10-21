
#include <iostream>
#include <queue>
#include <string>
#include <stdexcept>
using namespace std;

// Services

class EmailService
{
public:
    void sendEmail(string to, string subject)
    {
        cout << "Sending Email to " << to
             << " | Subject: " << subject << "\n";
    }
};

class BackupService
{
public:
    void runBackup()
    {
        cout << "Running Backup\n";
    }
};

class CleanupService
{
public:
    void cleanTempFiles()
    {
        cout << "Cleaning Temporary Files\n";
    }
};

// Job

class Job
{
public:
    virtual void execute() = 0;
    virtual ~Job() = default;
};

class BackupJob : public Job
{
private:
    BackupService *backupService;

public:
    BackupJob(BackupService *service)
        : backupService(service) {}

    void execute() override
    {
        backupService->runBackup();
    }
};

class CleanUpJob : public Job
{
private:
    CleanupService *cleanupService;

public:
    CleanUpJob(CleanupService *service)
        : cleanupService(service) {}

    void execute() override
    {
        cleanupService->cleanTempFiles();
    }
};

class EmailJob : public Job
{
private:
    EmailService *emailService;

public:
    EmailJob(EmailService *service)
        : emailService(service) {}

    void execute() override
    {
        emailService->sendEmail(
            "user@gmail.com", "Welcome");
    }
};

// Job Factory

class JobFactory
{
public:
    static Job *createJob(string job)
    {
        if (job == "Email")
            return new EmailJob(new EmailService());

        else if (job == "Backup")
            return new BackupJob(new BackupService());

        else if (job == "Cleanup")
            return new CleanUpJob(new CleanupService());

        else
            throw invalid_argument("Wrong Job Argument");
    }
};

// Job Queue

class JobQueue
{
private:
    queue<Job *> jobQ;

public:
    void submit(Job *job)
    {
        jobQ.push(job);
        cout << "Job Submitted\n";
    }

    Job* take()
    {
        if (jobQ.empty())
        {
            cout << "No Job Left\n";
            return nullptr;
        }

        Job *job = jobQ.front();
        jobQ.pop();

        return job;
    }

    bool empty()
    {
        return jobQ.empty();
    }
};

// WORKER

class Worker
{
private:
    JobQueue* jobQueue;

public:
    Worker(JobQueue *queue)
        : jobQueue(queue) {}

    void run()
    {
        while (!jobQueue->empty())
        {
            Job *job = jobQueue->take();

            if (job != nullptr)
            {
                job->execute();
                delete job;
            }
        }
    }
};


int main()
{
    JobQueue *j =  new JobQueue();

    j->submit(JobFactory::createJob("Email"));
    j->submit(JobFactory::createJob("Backup"));
    j->submit(JobFactory::createJob("Cleanup"));

    Worker worker(j);

    worker.run();

    delete j;
    return 0;
}
