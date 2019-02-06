<link rel="stylesheet" href="_github-markdown.css">

# Scrum

	Waterfall = plan -> build -> test -> review -> deploy
	Waterfall is not agile enough
	Scrum = ~3week(plan + build + test + review) = potentiall shippable product
	Scrum = Sum of Sprints
	Sprint = incremental releases
		= 1 - 3 week

# 3 Roles
## Product Owner
	Defines the features
## Scrum Master
	Servant Leader to the Team
	Protects the Team and the Process
## Team

# 3 Artifacts
## Product Backlog
	Product Owner creates a prioritized list of features = user stories.
	This document changes with every sprint.

## User Stories
	Describes a feature set, with the Schema
		As a ___
		I need ___
		So that ___
	These will go to the Backlog and estimated.

## Burndown Chart
	Show the progress during the sprint.

# 3 Ceremonies
## Sprint Planning
	Discuss user stories and estimate their relative sizes.
	*Planning Poker* helps to estimate the size!

## Daily Scrum
	Brief stand-up meeting, the team discusses what they have completed, what they are working on and possible blocking points.
	Clarify: what can we do to solve blocking points?
	*Agile Board* visizalizes progress of the items.

## Sprint Review
	A retrospective, occurs at the end of the sprint.
	The team demonstrates the completed work to the Product Owner.
	Discuss what they can do to improve the process going forward.
	*Done Pile* ~= list of completed items at the end of the Sprint.

# Workflow:
	1. Start with the Product Backlog
		where the Product Owner builds a list of the bright ideas and features
		The Product Owner prioritizes the list and brings the top items to the team.
	2. Sprint planning
		Product Owner and Scrum Master discusses the top priority user stories.
		Discuss what can go into the next sprint.
	3. Maintain the Sprint Backlog
		List the user stories which are committed to for the next sprint.
	4. Sprint = 1 - 3 week time box
		with Daily Stand-up
	5. Output = potentially shippable product
	6. Sprint Review & Retrospective meeting
		The Team shows the product to the Product Owner
		What can be done to improve the process?
	
	Repeat this workflow for each Sprint.

<img src="scrum.cheatsheet.png" width="550px">

# Kanban
	has also Backlog
	has Kanban Board (~Agile Board)
	has daily Stand-up
	has Done Pile
## Kanban's specialities of Scrum:
	There is no Sprint, no Sprint Planning, not necessarily Retrospective!
	Card of the Board flow accross the board continuously!
	No specific release day, it is up to the team to decide when to package for a release.
		(in practice, the release slightly more often than in pure Scrum)
## Kanban Board
	has often more items on the board than a Scrum-Board, because not only tasks of the current sprint are on it.
### Danger:
	1. lost effective transition from backlog to dev
	2. hard limit on WIP, too much WIP
### Solution to limit WIP:
	1. Build a Board which allows only max. 5 items in a column.
	2. talk about the work, face-to-face where possible
	3. release often
	4. regular demos to stakeholders

## Scrum vs Kanban
<img src="scrum.vs.kanban.png" width="550px">

## Large companies, like SIEMENS, use Kanban
<img src="scrum.kanban_at_siemens.png" width="550px">

## Bossless-ness relies on self-organization
<img src="scrum_is_bossless.png" width="550px">

## Is Scrum the right solution for you?
<img src="scrum_suited_or_not.png" width="550px">

## Scrumban:
<img src="scrumban.png" width="550px">

# SAFe
<img src="safe.png" width="550px">

1. SAFe is based on Scrum.
2. Scrum is for **small** teams
3. SAFe is for the coordination of **multiple teams** & their dependencies
4. SAFe = a set of organization and workflow patterns intended to guide enterprises in scaling lean and agile practices.
5. Foundation: **Lean-Agile Leadership**
6. Contains:
	1. has **Agile Release Train (ART)**
		1. consists of 5 - 15 teams (up to 100 individuals) that build a solution together
		2. has **RTE = Release Train Engineer**, he coordinates & plannes the release
	2. has PI planning: Roadmap & Product increment
		1. a 2-day workshop for planning the next release
	3. has Hardening/Polish Sprint: the last sprint of a quarter
		1. ~ H.I.P. Sprint: Hardening, Innovation, Planning
7. Configurations:
	1. Essential SAFe - one agile release train (ART).
		1. One Solution
	2. Large Solution SAFe - more than one ART
		1. One Solution
	3. Portfolio SAFe
		1. more than one solution
	4. Full SAFe - both portfolio and large solution needed
8. Ceremonies of SAFe
	1. PI Planning: every 10. week, where all teams and management comes together
	2. PO weekly meetings:
		2. PO Sync: synchronization and statusupdate with RTE, Sys Architect, PM
		3. PO Info: infos given from different projects or new info will be delivered to the teams
		4. PO Grooming: clarifications of requirements for the next PI planning
## Challenges in SAFe:
<img src="safe.challenges.1.png" width="550px">
<img src="safe.challenges.2.png" width="550px">
<img src="safe.challenges.3.png" width="550px">
<img src="safe.challenges.4.png" width="550px">
<img src="safe.challenges.5.png" width="550px">
<img src="safe.challenges.6.png" width="550px">

### Solutions for SAFe challenges:
1. Use dependency board!
2. learn from old estimation to estimate better in the future
3. plan the delivery of (external) dependencies
4. use only 1 method of reporting (eg Jira), is more transparent
5. try not to do micromanagement & try to keep the teams autonom as far as possible! (if you have mature teams!)
6. Tag dependencies in Jira with #has2bedoneby... or #hastobeuntil...
7. ensure that SAFe teams already know Scrum well!
