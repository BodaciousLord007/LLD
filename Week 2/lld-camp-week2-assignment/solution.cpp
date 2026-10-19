
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <unordered_set>
#include <stdexcept>
#include <utility>

using namespace std;

// ================= VALUE OBJECTS =================

struct Date
{
    int day;
    int month;
    int year;
};

struct Password
{
    string value;
};

struct Message
{
    string value;
};

enum class EnrollmentStatus
{
    ACTIVE,
    COMPLETED
};

// ================= LESSON =================

class Lesson
{
private:
    int id;
    string title;
    string contentUrl;
    int durationMinutes;

public:
    Lesson(int id, string title, string url, int duration)
        : id(id),
          title(move(title)),
          contentUrl(move(url)),
          durationMinutes(duration) {}

    int getId() const
    {
        return id;
    }

    string getTitle() const
    {
        return title;
    }

    string getContentUrl() const
    {
        return contentUrl;
    }

    int getDurationMinutes() const
    {
        return durationMinutes;
    }
};

// ================= MODULE =================

class Module
{
private:
    int id;
    string title;
    list<Lesson> moduleLessons;

public:
    Module(int id, string title)
        : id(id), title(move(title)) {}

    int getId() const
    {
        return id;
    }

    string getTitle() const
    {
        return title;
    }

    void addLesson(const Lesson &lesson)
    {
        moduleLessons.push_back(lesson);
    }

    const list<Lesson> &getLessons() const
    {
        return moduleLessons;
    }
};

// ================= COURSE =================

class Course
{
private:
    int id;
    string title;
    string description;
    int instructorId;
    list<Module> courseModules;

public:
    Course(int id, string title, string description, int instructorId)
        : id(id),
          title(move(title)),
          description(move(description)),
          instructorId(instructorId) {}

    int getId() const
    {
        return id;
    }

    string getTitle() const
    {
        return title;
    }

    int getInstructorId() const
    {
        return instructorId;
    }

    void addModule(const Module &module)
    {
        courseModules.push_back(module);
    }

    const list<Module> &getModules() const
    {
        return courseModules;
    }

    bool containsLesson(int lessonId) const
    {
        for (const auto &module : courseModules)
        {
            for (const auto &lesson : module.getLessons())
            {
                if (lesson.getId() == lessonId)
                    return true;
            }
        }
        return false;
    }

    int getTotalLessons() const
    {
        int total = 0;

        for (const auto &module : courseModules)
        {
            total += static_cast<int>(module.getLessons().size());
        }

        return total;
    }
};

// ================= USER =================

class User
{
private:
    int id;
    string name;
    string email;
    string passwordHash;

public:
    User(int id, string name, string email, string passwordHash)
        : id(id),
          name(move(name)),
          email(move(email)),
          passwordHash(move(passwordHash)) {}

    virtual ~User() = default;

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    string getEmail() const
    {
        return email;
    }
};

// ================= STUDENT =================

class Student : public User
{
public:
    Student(int id, string name, string email, string passwordHash)
        : User(id, move(name), move(email), move(passwordHash)) {}
};

// ================= INSTRUCTOR =================

class Instructor : public User
{
public:
    Instructor(int id, string name, string email, string passwordHash)
        : User(id, move(name), move(email), move(passwordHash)) {}
};

// ================= ENROLLMENT =================

class Enrollment
{
private:
    int id;
    int studentId;
    int courseId;
    Date enrollmentDate;

    EnrollmentStatus status = EnrollmentStatus::ACTIVE;
    unordered_set<int> completedLessonIds;

public:
    Enrollment(int id, int studentId, int courseId, Date date)
        : id(id),
          studentId(studentId),
          courseId(courseId),
          enrollmentDate(date) {}

    int getId() const
    {
        return id;
    }

    int getStudentId() const
    {
        return studentId;
    }

    int getCourseId() const
    {
        return courseId;
    }

    EnrollmentStatus getStatus() const
    {
        return status;
    }

    void markLessonCompleted(int lessonId, int totalLessons)
    {
        completedLessonIds.insert(lessonId);

        if (totalLessons > 0 &&
            completedLessonIds.size() >=
                static_cast<size_t>(totalLessons))
        {
            status = EnrollmentStatus::COMPLETED;
        }
    }

    float getProgressPercent(int totalLessons) const
    {
        if (totalLessons == 0)
            return 0.0f;

        return 100.0f * completedLessonIds.size() / totalLessons;
    }
};

// ================= RIGHT PART =================

// ================= NOTIFICATION INTERFACE =================

class INotificationChannel
{
public:
    virtual void send(const User &user, const Message &message) = 0;

    virtual ~INotificationChannel() = default;
};

// ================= EMAIL NOTIFICATION =================

class EmailNotificationChannel : public INotificationChannel
{
public:
    void send(const User &user, const Message &message) override
    {
        cout << "[EMAIL] To: " << user.getEmail()
             << " | Message: " << message.value << '\n';
    }
};

// ================= SMS NOTIFICATION =================

class SmsNotificationChannel : public INotificationChannel
{
public:
    void send(const User &user, const Message &message) override
    {
        cout << "[SMS] User: " << user.getName()
             << " | Message: " << message.value << '\n';
    }
};

// ================= COURSE REPOSITORY INTERFACE =================

class ICourseRepository
{
public:
    virtual Course *findById(int id) = 0;

    virtual vector<Course *> findByInstructor(int instructorId) = 0;

    virtual void save(const Course &course) = 0;

    virtual ~ICourseRepository() = default;
};

// ================= IN-MEMORY COURSE REPOSITORY =================

class InMemoryCourseRepository : public ICourseRepository
{
private:
    map<int, Course> courses;

public:
    void save(const Course &course) override
    {
        courses.insert_or_assign(course.getId(), course);
    }

    Course *findById(int id) override
    {
        auto it = courses.find(id);

        if (it == courses.end())
            return nullptr;

        return &it->second;
    }

    vector<Course *> findByInstructor(int instructorId) override
    {
        vector<Course *> result;

        for (auto &[id, course] : courses)
        {
            if (course.getInstructorId() == instructorId)
            {
                result.push_back(&course);
            }
        }

        return result;
    }
};

// ================= ENROLLMENT REPOSITORY INTERFACE =================

class IEnrollmentRepository
{
public:
    virtual Enrollment *findById(int id) = 0;

    virtual Enrollment *findByStudentAndCourse(
        int studentId, int courseId) = 0;

    virtual void save(const Enrollment &enrollment) = 0;

    virtual ~IEnrollmentRepository() = default;
};

// ================= IN-MEMORY ENROLLMENT REPOSITORY =================

class InMemoryEnrollmentRepository : public IEnrollmentRepository
{
private:
    map<int, Enrollment> enrollments;

public:
    void save(const Enrollment &enrollment) override
    {
        enrollments.insert_or_assign(
            enrollment.getId(), enrollment);
    }

    Enrollment *findById(int id) override
    {
        auto it = enrollments.find(id);

        if (it == enrollments.end())
            return nullptr;

        return &it->second;
    }

    Enrollment *findByStudentAndCourse(
        int studentId, int courseId) override
    {
        for (auto &[id, enrollment] : enrollments)
        {
            if (enrollment.getStudentId() == studentId &&
                enrollment.getCourseId() == courseId)
            {
                return &enrollment;
            }
        }

        return nullptr;
    }
};

// ================= ENROLLMENT SERVICE =================

class EnrollmentService
{
private:
    ICourseRepository &courseRepository;
    IEnrollmentRepository &enrollmentRepository;
    INotificationChannel &notificationChannel;

    // Non-owning references to students for demo notifications.
    map<int, const Student *> enrolledStudents;

    int nextEnrollmentId = 1;

public:
    EnrollmentService(
        ICourseRepository &courseRepo,
        IEnrollmentRepository &enrollmentRepo,
        INotificationChannel &notifier)
        : courseRepository(courseRepo),
          enrollmentRepository(enrollmentRepo),
          notificationChannel(notifier) {}

    int enrollStudent(
        const Student &student,
        int courseId,
        Date date)
    {
        Course *course = courseRepository.findById(courseId);

        if (course == nullptr)
            throw runtime_error("Course not found");

        if (enrollmentRepository.findByStudentAndCourse(
                student.getId(), courseId) != nullptr)
        {
            throw runtime_error("Student already enrolled");
        }

        int enrollmentId = nextEnrollmentId++;

        Enrollment enrollment(
            enrollmentId,
            student.getId(),
            courseId,
            date);

        enrollmentRepository.save(enrollment);

        enrolledStudents[enrollmentId] = &student;

        notificationChannel.send(
            student,
            {"You have been enrolled in " + course->getTitle()});

        return enrollmentId;
    }

    void completeLesson(int enrollmentId, int lessonId)
    {
        Enrollment *enrollment =
            enrollmentRepository.findById(enrollmentId);

        if (enrollment == nullptr)
            throw runtime_error("Enrollment not found");

        Course *course =
            courseRepository.findById(enrollment->getCourseId());

        if (course == nullptr)
            throw runtime_error("Course not found");

        if (!course->containsLesson(lessonId))
            throw runtime_error("Lesson does not belong to course");

        if (enrollment->getStatus() == EnrollmentStatus::COMPLETED)
            return;

        enrollment->markLessonCompleted(
            lessonId,
            course->getTotalLessons());

        if (enrollment->getStatus() == EnrollmentStatus::COMPLETED)
        {
            auto it = enrolledStudents.find(enrollmentId);

            if (it != enrolledStudents.end())
            {
                notificationChannel.send(
                    *it->second,
                    {"You have completed the course " +
                     course->getTitle()});
            }
        }
    }

    float getProgressPercent(int enrollmentId)
    {
        Enrollment *enrollment =
            enrollmentRepository.findById(enrollmentId);

        if (enrollment == nullptr)
            throw runtime_error("Enrollment not found");

        Course *course =
            courseRepository.findById(enrollment->getCourseId());

        if (course == nullptr)
            throw runtime_error("Course not found");

        return enrollment->getProgressPercent(
            course->getTotalLessons());
    }
};

// ================= MAIN / DEMO =================

int main()
{
    try
    {
        // 1. Create Instructor
        Instructor instructor(
            1, "John", "john@example.com", "demo-hash");

        // 2. Create Lessons
        Lesson lesson1(101, "Introduction to C++", "url1", 30);
        Lesson lesson2(102, "Classes and Objects", "url2", 40);
        Lesson lesson3(103, "Inheritance", "url3", 45);
        Lesson lesson4(104, "Polymorphism", "url4", 35);

        // 3. Create Modules
        Module module1(201, "C++ Basics");
        module1.addLesson(lesson1);
        module1.addLesson(lesson2);

        Module module2(202, "Object Oriented Programming");
        module2.addLesson(lesson3);
        module2.addLesson(lesson4);

        // 4. Create Course
        Course course(
            301,
            "Modern C++",
            "Learn C++ and OOP",
            instructor.getId());

        course.addModule(module1);
        course.addModule(module2);

        // 5. Create Repositories
        InMemoryCourseRepository courseRepo;
        InMemoryEnrollmentRepository enrollmentRepo;

        // 6. Save Course
        courseRepo.save(course);

        // 7. Create Student
        Student student(
            2, "Alice", "alice@example.com", "demo-hash");

        // 8. Create Notification Channel
        EmailNotificationChannel emailNotifier;

        // 9. Dependency Injection
        EnrollmentService service(
            courseRepo,
            enrollmentRepo,
            emailNotifier);

        // 10. Enroll Student
        int enrollmentId = service.enrollStudent(
            student,
            course.getId(),
            {15, 10, 2026});

        Enrollment *enrollment =
            enrollmentRepo.findById(enrollmentId);

        auto printStatus = [&]()
        {
            cout << "Status: "
                 << (enrollment->getStatus() ==
                             EnrollmentStatus::COMPLETED
                         ? "COMPLETED"
                         : "ACTIVE")
                 << '\n';
        };

        cout << "\nAfter Enrollment:\n";
        printStatus();

        // 11. Complete Lessons
        cout << "\nCompleting Lessons:\n";

        for (int lessonId : {101, 102, 103, 104})
        {
            service.completeLesson(enrollmentId, lessonId);

            cout << "Completed Lesson: " << lessonId << '\n';

            cout << "Progress: "
                 << service.getProgressPercent(enrollmentId)
                 << "%\n";
        }

        // 12. Final State
        cout << "\nFinal Enrollment State:\n";

        printStatus();

        cout << "Final Progress: "
             << service.getProgressPercent(enrollmentId)
             << "%\n";
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
