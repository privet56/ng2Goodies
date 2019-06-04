<link rel="stylesheet" href="../_github-markdown.css">

# Git / Gitflow
Branches, used by gitflow:
1. master
2. develop
3. feature branches

# gitflow
```sh
$ git flow init
# push into current branch, eg. develop, not to master!
$ git push origin --all

# this *switches* to feature/myfeature - branch
$ git flow feature start myfeature
$ git add .
$ git commit -m "implementing feature..."
$ git push --set-upstream origin feature/myfeature

# other dev can checkout & work on the pushed code:
$ git checkout feature/myfeature

# this pushes to remote repo (creates myfeature remotely)
$ git flow feature publish myfeature
$ git commit -am "updated myfeature"    #a = git add (does add changes, does not add new files!)
$ git push origin feature/myfeature


# do this when feature implementation finished,
## this merges the code into the develop branch
## this *switches* back to the develop branch
## this deletes(=closes) the feature branch
$ git flow feature finish [myfeature]
# this pushes the feature-branch-code (now locally merged in develop)
$ git push --set-upstream origin develop


# this cmd *switches* to new branch release/1.0.1
$ git flow release start 1.0.1
$ git add .
$ git commit -m "preparing release, increasing package.json version number"
# this merges the changes into master, creates a tag(!)
$ git flow release finish

$ git checkout master
# push with the above created tag(!)
$ git push origin --all --follow-tags
```
### Miscellaneous git commands:
```ps
$ git branch        # lists existing branches, marks current branch
$ git status        # shows current branch, lists untracked files

$ git remote add origin git@github.com:myusername/myproject.git
$ git remote -v     # lists origin

$ git checkout develop   # downloads the dev branch & switches to this branch
$ git push origin develop

$ git flow feature  # prints current feature name
```
### What is the difference between git pull & git fetch?
**git pull** does a **git fetch** followed by a **git merge**

**git pull** is what you do to bring a local branch up-to-date with its remote version.



