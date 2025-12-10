# Common
Problems

<br> 
//https://godbolt.org/       runtime check compiler link

git add .                                                                 //add
git commit -m "Initial commit"                                            //commit

git remote add origin https://github.com/yourname/yourrepo.git            //link to github   
git push -u origin main                                                   //push all the contents to the github

git status                                                                //to check the changes




 <h1>git add</h1>

1. Stage all changes

git add .
Stages all new, modified, and deleted files in the current directory and its subdirectories only.



git add -A
Stages all changes (new, modified, deleted files) across the entire repository, no matter which directory you are in.



git add --all
Exactly the same as git add -A.




2. Stage a single file
git add filename
git add "abc.cpp"



3. Stage multiple specific files
git add file1.cpp file2.cpp file3.cpp
git add "file 1.cpp" "file 2.cpp"



4. Stage files by pattern
git add *.cpp       # all .cpp files in current directory
git add src/*.h     # all .h files in src folder
git add '**/*.txt'  # all .txt files recursively (with Git >= 2.0 and shell support)



5. Stage parts of a file (interactive / patch)
git add -p filename
git add --patch filename
Lets you choose hunks of changes to stage instead of the whole file.



6. Stage directories
git add src/
git add "my folder/"
Adds all files inside the directory (recursively).



7. Stage only modified files (skip new untracked files)
git add -u
git add --update
Stages changes to tracked files only (modified/deleted), ignores new untracked files.



8. Interactive mode
git add -i
Opens an interactive menu to stage, unstage, patch, or view changes.




9. Stage all new files (untracked only)
git add -N .
Adds new files as “intent to add” (staged for next commit but content not added yet).



10. Force add ignored files
git add -f filename
git add --force filename
Adds files that are ignored by .gitignore.




11. Dry-run (preview)
git add --dry-run .
Shows what would be staged without actually staging.










<h1>git commit</h1>

1. Basic commit
git commit -m "Your commit message"
Commits staged changes with the given message.

2. Commit all changes (without git add)
git commit -a -m "Your message"
Automatically stages all modified and deleted tracked files before committing.
Does NOT include new untracked files.

3. Commit with verbose output
git commit -v -m "Message"
Shows the diff of changes in your commit message editor.

4. Commit interactively / selectively
git commit -p
Lets you select hunks/parts of files to commit.
Works like git add -p, but for committing.

5. Amend last commit
git commit --amend
git commit --amend -m "Updated message"
Modifies the most recent commit, either by changing its message or adding staged changes.

6. Commit with a template
git commit -t template.txt
Uses a template file for the commit message.

7. Sign commits (GPG)
git commit -S -m "Signed commit"
Creates a GPG-signed commit for authenticity.

8. Commit only certain files
git commit file1.cpp file2.txt -m "Message"
Commits specific staged files only.

9. Commit without editing message
git commit --no-edit
Skips opening the editor when amending commits.

10. Allow empty commit
git commit --allow-empty -m "Empty commit"
Creates a commit even if there are no changes. Useful for triggers or marking milestones.

11. Include status in commit message
git commit -v
Shows diff + status in the editor when writing a commit message.

12. Specify author
git commit --author="Name <email@example.com>" -m "Message"
Overrides the commit author for this commit.

13. Date override
git commit --date="YYYY-MM-DD HH:MM:SS" -m "Message"
Overrides the commit timestamp.








<h1>git push</h1>
1. Basic push
git push
Pushes the current branch to its upstream (remote) branch.

2. Push to a specific remote
git push origin
git push origin main
origin → the remote repository name (default is origin)
main → the branch name to push

3. Push a new branch
git push -u origin new-branch
Creates a new branch on the remote and sets it as upstream for local tracking.

4. Force push
git push --force
git push -f
Overwrites the remote branch history with your local commits.
Use with caution!

5. Force-with-lease (safer)
git push --force-with-lease
Only forces the push if the remote branch hasn’t been updated by others.
Safer than --force.

6. Push tags
git push --tags
Pushes all local tags to the remote.
Push a single tag:
git push origin v1.0

7. Delete remote branch
git push origin --delete branch-name
Removes a branch from the remote repository.

8. Push all branches
git push --all
Pushes all local branches to the remote.

9. Push with dry-run
git push --dry-run
Shows what would be pushed without actually pushing.

10. Set upstream
git push --set-upstream origin branch-name
git push -u origin branch-name
Sets the remote tracking branch for the current local branch.
Useful when pushing a new branch for the first time.

11. Push with tags and prune
git push --prune
Deletes remote branches that no longer exist locally (prunes stale branches).










<h1>git status</h1>

1. Basic status
git status
Shows the current branch, staged changes, unstaged changes, and untracked files.



2. Short format
git status -s
git status --short

Shows a compact, two-letter format:
?? → untracked files
M → modified but unstaged
A → staged for addition
D → staged for deletion



3. Branch information
git status -b
git status --branch
Shows current branch and tracking info in addition to normal status.



4. Show ignored files
git status --ignored
Lists files ignored by .gitignore.
Can be combined with short format:
git status -s --ignored



5. Show untracked files only
git status --untracked-files
git status --untracked-files=all    # default
git status --untracked-files=no     # hides untracked files
git status --untracked-files=normal # only untracked files in the current directory



6. Display in porcelain format (for scripts)
git status --porcelain
Provides a stable, easy-to-parse format for scripts.
Works with --short and --branch as well.



7. Display ahead/behind tracking info
git status -b
Shows how many commits your branch is ahead/behind the remote.



8. Verbose
git status -v
git status --verbose
Prints status of ignored files (if combined with --ignored).



Summary
git status → full human-readable status
git status -s → short format
git status -b → shows branch info
git status --ignored → includes ignored files
git status --porcelain → machine-readable









<h1>git pull</h1>

1. Basic pull
git pull
Fetches changes from the remote and merges them into your current branch.



2. Pull from a specific remote and branch
git pull origin main
origin → remote name
main → branch name



3. Rebase instead of merge
git pull --rebase
git pull --rebase=interactive
Applies your local commits on top of fetched changes instead of merging.
Keeps a linear history.



4. Specify a particular remote branch
git pull origin feature-branch
Pulls changes from the feature-branch on origin and merges/rebases into your current branch.



5. Pull with fast-forward only
git pull --ff-only
Only performs the pull if it can be fast-forwarded; avoids creating a merge commit.



6. Pull with a specific strategy
git pull -s recursive -X theirs
git pull -s recursive -X ours
-s → merge strategy
-X theirs/ours → strategy options to resolve conflicts automatically



7. Pull only fetch (without merge)
git fetch origin
Technically not git pull, but equivalent if you only want to update remote-tracking branches without merging.



8. Verbose
git pull --verbose
Shows detailed info about what is being fetched and merged.




9. Allow unrelated histories
git pull --allow-unrelated-histories
Useful if you are pulling from a repository with no common ancestor.



10. Commit message for merge
git pull --edit
Opens editor to edit the merge commit message after pulling.



11. Rebase interactive
git pull --rebase=interactive
Lets you edit or squash local commits during the rebase after fetching.




Summary
git pull = fetch + merge (default)
git pull --rebase = fetch + rebase
git pull --ff-only = only fast-forward merge
git pull origin branch = pull from specific remote branch
git pull --verbose = detailed info
git pull --allow-unrelated-histories = merge unrelated repos








<h1>git branch</h1>


1. List all branches
git branch
Lists all local branches in the repository.
The current branch is highlighted with a *.




2. List remote branches
git branch -r
Shows all branches on the remote (e.g., origin/main).



3. List all local + remote branches
git branch -a
Lists both local and remote-tracking branches.




4. Create a new branch
git branch new-branch
Creates a new branch locally.
Does not switch to the branch automatically.



5. Create and switch to a new branch
git checkout -b new-branch
# or (Git 2.23+)
git switch -c new-branch
Creates and checks out the branch in one step.




6. Delete a branch
git branch -d branch-name
Deletes a local branch if it has been merged.
git branch -D branch-name
Force deletes a local branch even if unmerged.



7. Rename a branch
git branch -m old-name new-name
Renames a local branch.




8. Set upstream (tracking) branch
git branch -u origin/branch-name
Sets the remote branch to track for the current local branch.



9. Show last commit for each branch
git branch -v
Shows the latest commit hash and message for each branch.



10. Show branches merged/unmerged
git branch --merged
Lists branches already merged into the current branch.
git branch --no-merged
Lists branches not yet merged into the current branch.



11. Show all branch details
git branch -vv
Shows branches, tracking info, and last commit.



12. Delete remote branch
git push origin --delete branch-name
Not technically git branch, but this is how you delete a branch on remote.



Summary
git branch → list local branches
git branch -r → list remote branches
git branch -a → list all branches
git branch branch-name → create branch
git branch -d/-D branch-name → delete branch
git branch -m old new → rename branch
git branch -v / -vv → show last commit & tracking info
git branch --merged / --no-merged → merged/unmerged branches





















<h1>git stage</h1>


1. Stage all changes
git stage .
Equivalent to git add .
Stages all new, modified, and deleted files in the current directory and subdirectories.
git stage -A
git stage --all
Equivalent to git add -A / --all
Stages all changes in the repository.




2. Stage single file
git stage file.cpp
Equivalent to git add file.cpp



3. Stage multiple files
git stage file1.cpp file2.cpp
Equivalent to git add file1.cpp file2.cpp



4. Stage parts of a file (interactive)
git stage -p file.cpp
Equivalent to git add -p file.cpp
Lets you stage hunks of changes instead of the whole file.



5. Stage directories
git stage src/
Equivalent to git add src/
Stages all files in the folder recursively.



6. Stage only modified/deleted tracked files
git stage -u
Equivalent to git add -u
Stages modified and deleted files only, ignores new untracked files.



7. Force add ignored files
git stage -f file
Equivalent to git add -f file
Adds files ignored by .gitignore.



✅ Conclusion:
git stage is mostly just another name for git add.
All options and usage of git add work with git stage.






</br>
