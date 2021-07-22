# Internship Guideline

Welcome to Ekbana AI team!

This is a guideline to make you familiar with working methodolgy in the team. Please go through each of the following in great detail so that you feel comfortable with the work environment and practices.

## Operating System:

We strongly recommend (actually urge) to you linux based operating systems. You can install latest (or recent) LTS version of Ubuntu Linux. You may choose to have a dual boot in your system if you have some exigencies related to other operating systems. Make sure you safely backup your disk's content or take necessary precautions before formatting your partition for linux installation. You must be familiar with the basic linux commands including but not limited to the following:
```
pwd, cd, ls, cat, cp, mv, mkdir, rmdir, rm, touch, locate, find, grep, sudo, df, du, head, tail, diff, tar, chmod, chown, jobs, kill, ping, wget, uname, top, history, man, echo, zip, unzip, hostname, useradd, userdel, apt.
```
## IDE and Code Editor:
Any IDE and code editor that is supported by linux is fine. VSCode is quite popular, lightweight and flexible one, but feel free to choose any one of your choice.

Since we often need to work on servers in command line, you MUST have basic familiarity with one of the terminal based editors. (eg. VIM, nano).

## Version Control System
You project, internship tasks are always required to be maintained in GIT version control system. You should be familiar with at least the basics of following commands in git:
* git init
* git config
* git status
* git add
* git commit
* git reset
* git stash
* git branch
* git checkout
* git remote
* git pull
* git push
* git merge
* git rebase

You also need to understand the concept of ".gitignore" properly. Also, note that there are programming language specific recommendations for '.gitignore'. So, make sure you understand that well for all languages you will be using.

## Project and tasks management

All the tasks you do (in your internship or in other projects) are maintained in a project in gitlab repository. The repository is maintained at our internal gitlab server. The URL would appear in this format:

`https://repo.ekbana.info/<your-project-path>/`


The details of your tasks are assigned in following subsection:

### Tasks
Tasks are listed as _issues_ in the "boards" section of your gitlab. Each issue represents a specific task and the description of the task can be seen the in the description section of that issue. You can find the relevant links or references sometimes in that description or just the elaboration of the job you need to do in that task in the description.

You can go to the boards via issue sections of the web GUI or directly via the following link:

`https://repo.ekbana.info/<your-project-path>/-/boards`

The link to an individual task would looks something like this:

`https://repo.ekbana.info/<your-project-path>/-/issues/<issue-number>`

### Task Status
Task status refers to the status or current state of the task you are working on. Task status are maintained using "labels" and each label has a board corresponding to it. Task status could be "ToDo", "Doing", "Done", "Reviewing", "Reviewed" and so on. Tasks that are created as an issue but not yet labelled are listed under "Open" tab and completed (or sometimes discarded) tasks are in the "Closed".

You can change the status of your task by either dragging and dropping your tasks from one board to other in the boards' web GUI or by using following commands via gitlab comments for that issue.

`/unlabel <old-label>`  
`/label <new-label>`

For example if you want to start doing a task that is in your "ToDo" board, then you could do:

`/unlabel ~"ToDo"`
`/label ~"Doing"`

### Task Updates
Progresses or updates in tasks are maintained by commenting on your task (i.e. by commenting on your issue). You are required to be verbose in your comments describing your approaches in doing that task.

You can tag other team members typing the '@' symbol followed by the username and reference other issues and merge requests using '#' and '!' symbols respectively.

Gitlab comments support `MARKDOWN` formatting. Make extensive use of that. If you have not used markdown before, go through [this tutorial](https://www.markdownguide.org/basic-syntax/). Never paste a screenshot of codes or error messages, but rather copy the text and highlight it or use markdown formatting.

### Time Log
You are required to log the amount of time you have spent to so the task using the `/spend` command in the comments. You can do so whenever you make your update comments in your task's issue. Logging your time is very important as this is considered as one of the metrics for your performance review. So don't forget to update your time log in frequent intervals. Just to give you the context, since we have 9 hours as office hours and 1 hour break in total, your daily time log could likely be around 8H in a day with average workload.

Command for time log in comments:
`/spend <time>`

eg. `/spend 2h`

### Task Submission
Once you are done with your tasks or at any important benchmark, your work (which could be a piece of code, or some documentation) is committed and pushed to your repository. Take care of the following points while or before doing so:

* make sure you have configured your git username and email on repo (using `git config` command.)
* make sure you have configured SSH keys at your repository (i.e. generate public-private RSA key pair and add the public key to your repository's setting)
* create a branch for each of your tasks and have the branches aptly named. Always create the branch for your tasks from the `master` branch.
* make sure you have a properly organized folder structure for your project. Each task or related tasks could go inside same folder, with each folder (or subfolder) representing your particular task.
* make sure you have added only strictly required files in your commit. Avoid using wild commands like `git add *` whenever you can or use it with caution.
* make sure you have ignored the unnecessary files using gitignore.
* be specific on your commit messages. Mention exactly what task the particular commit reflects.
* be apt on your commit messages so that the reviewer could get a quick glimpse of your task done in that particular commit thorough your commit message. Also, it would help you to revert back your older states whenever necessary.
* create a merge request corresponding to your branch whenever you have completed the task (and assign it to your reviewer if necessary)
* keep rebasing your work branch frequently with master branch if you are working on multiple related tasks or collaborating in group.

## Documentation:
Always consider documentation as a part of your work. In particular if you are designated with a study or research related task, an elaborate documentation is a must. The documentations should be a markdown (`.md`) file with proper formatting, properly linked images or hyperlinks if necessary. The documentations should be committed along with the codes and pushed to the repo for long term usage. It could act as a note or summary of your literature review that you might need to look back in future as well.

## Monthly Report
At the end of every month you are required to present a monthly report to your team-lead. This should contain the details of works and learnings you have made during that period. The document itself can be a markdown document or a google document that can be compiled to a pdf file.

## Presentation
At the end of your internship period, you will be given (or maybe you can choose) a research problem that you will extensively research upon and perform some experiments with it. This usually includes implementing a research paper or a part of it, solving a novel problem of interest or requirement in the team. You are required to deliver a technical presentation based on that research problem and your approach to it aided with a presentation slide.

