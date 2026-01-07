Jira = Issues / Tasks / Bugs tracking tool

In companies, everything is tracked via Jira tickets:
Bugs 🐞
New features ✨
Tasks 🧩
Test failures ❌


How to CREATE a Jira Ticket (Step-by-Step)
🖼️ Pictorial Flow
Jira Dashboard
     |
     |--> [+ Create]
              |
              |--> Project: C++_Core_Engine
              |--> Issue Type: Bug
              |--> Summary: Segmentation fault on startup
              |--> Description: Steps to reproduce
              |--> Priority: High
              |--> Assignee: (Optional)
              |
           [ Create ]


Example Ticket Details (Realistic)
| Field               | Example                                  |
| ------------------- | ---------------------------------------- |
| **Issue Type**      | Bug                                      |
| **Summary**         | App crashes on startup                   |
| **Description**     | Crash occurs when config file is missing |
| **Environment**     | Linux Ubuntu 22.04                       |
| **Priority**        | High                                     |
| **Affects Version** | v2.1                                     |
| **Attachment**      | crash_log.txt                            |

📌 In real projects → QA / Tester usually creates the ticket.




How to SEE Jira Tickets Assigned to YOU
🖼️ Pictorial Demo
Top Menu
   |
   |--> Filters
          |
          |--> Advanced Issue Search
                     |
                     |--> Assignee = Current User
                     |
                 [Search]



Common Ways
✔️ Option 1: Quick Filter
JQL:
assignee = currentUser()

✔️ Option 2: Dashboards
Dashboard
  |
  |--> My Open Issues


📌 Corporate reality:
Every morning → check "Assigned to me"
That is your daily work list





What to LOOK INTO a Jira Ticket (C++ Project Focus)
🧠 Think like a Developer
🖼️ Ticket Anatomy
-------------------------------------
| BUG-1023                            |
| Crash in FileReader.cpp            |
-------------------------------------
| Description                        |
| Steps to Reproduce                 |
| Expected Result                    |
| Actual Result                      |
| Attachments (logs, dumps)          |
| Comments (QA / Dev discussion)     |
-------------------------------------



Key Sections You MUST Read
1️⃣ Description
What is failing?
Which module? (FileReader, MemoryManager, etc.)




2️⃣ Steps to Reproduce (VERY IMPORTANT)
1. Launch application
2. Load empty config
3. App crashes




3️⃣ Logs / Stack Trace
Example:
Segmentation fault
FileReader.cpp: line 87



4️⃣ Environment
OS
Compiler version
Debug / Release build



🧩 C++-Specific Checks
When fixing:
Null pointer dereference?
Memory leak?
Buffer overflow?
Wrong object lifetime?
Race condition?




Beginner Mistakes & Difficult Parts (VERY IMPORTANT)
❌ Common Mistakes

| Mistake                        | Why it Happens           |
| ------------------------------ | ------------------------ |
| Not reading ticket fully       | Jumping directly to code |
| Ignoring steps to reproduce    | Bug won’t reproduce      |
| Fixing symptom, not root cause | Bug comes back           |
| No local testing               | CI fails                 |
| Forgetting edge cases          | New crashes              |
| No comments in Jira            | Team confused            |



Difficult Parts You Must Be Careful About
🔸 Reproducing the Bug
"Works on my machine" ❌


Always:
Same OS
Same input
Same build flags

🔸 Legacy Code
Poor documentation
Unsafe pointers
Global state

🔸 Side Effects
Fixing one bug may break:
Another module
Performance
Thread safety



