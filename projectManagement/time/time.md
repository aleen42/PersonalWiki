## Project Time Management	[Back](./../projectManagement.md)

### 1. Processes

<img src="./processes.png">

1. Planning schedule management
    - A schedule management plan includes:
        - Project schedule model development
        - The scheduling methodology
        - Level of Accuracy and units of measure
        - Control thresholds(臨界值)
        - Rules of performance measurement
        - Reporting formats
        - Process descriptions
2. Defining activities
    - An **activity** or **task** is an element of work normally found on the work breakdown structure (WBS) that has an expected duration, a cost, and resource requirements
3. Sequencing activities
    - A **dependency** or **relationship** is the sequencing of project activities or tasks.
    - 3 types of dependencies:
        - **Mandatory dependencies(強制性依賴關係)**: inherent(固有的) in the nature of the work being performed on a project, sometimes referred to as hard logic.
        - **Discretionary dependencies(自由依賴關係)**: defined by the project team,  sometimes referred to as soft logic and should be used with care since they may limit later scheduling options.
        - **External dependencies**: involve relationships between project and non-project activities.
4. Estimating activity resources
    - **Resources**: people, equipment, and materials.
    - A **resource breakdown structure** is a hierarchical(分層的) structure that identifies the project's resources by category and type.
5. Estimating activity duration
    - **Duration** includes the actual amount of time worked on an activity plus elapsed(流逝的) time.
    - **Effort** is the number of workdays or work hours required to complete a task.
    - **Three-point estimates** are needed for PERT and Monte Carlo simulations(蒙特卡洛模擬).
6. Developing the schedule
    - tools:
        - **Gantt Charts**
        - **Critical Path Analysis**
        - **Critical Chain Scheduling**
        - **PERT Analysis**
7. Controlling the schedule

### 2. Activity Lists and Attributes

- An **activity list** is a tabulation(表格) of activities to be included on a project schedule that includes:
    - the activity name
    - an activity identifier or number
    - a brief description of the activity
- **Activity attributes** provide more information such as predecessors(前人), successors(繼承人), logical relationships, leads and lags(落後時間), resource requirements, constraints, imposed(強制的) dates, and assumptions related to the activity.

### 3. Milestones

- A **milestone** is a significant event that normally has no duration.
- Milestones should be 'SMART':
    - Specific
    - Mesuarable
    - Assignable
    - Realistic
    - Time-framed(時間有限的)

### 4. Network Diagrams

- A **network diagram** is a schematic(圖解的) display of the logical relationships among, or sequencing of, project activities.
    - **Arrow Diagramming Method(ADM)**: also called activity-on-arrow(AOA) network diagrams.
        - **Bursts(分開)** occur when a single node is followed by two or more activities.
        - A **merge(匯合)** occurs when two or more nodes precede(在...前面) a single node.
    - **Precedence Diagramming Method(PDM)**: activities are represented by boxes while relationships are represented by arrows.

### 5. Task Dependency Types

- **finish-to-start**(A finish-to-start B): B cannot start until A finishes.
- **start-to-start**(A start-to-start B): B cannot start until A starts
- **finsh-to-finish**(A finsh-to-finish B): B cannot finish until A finishes.
- **start-to-finish**(A start-to-finish B): B cannot finish until A starts.

### 6. Gantt Charts

- **Gantt Charts** provide a standard format for displaying project schedule information by listing project activities and their corresponding start and finish dates in a calendar format.
- Symbols:
    - a black diamond(◆): a milestone
    - a thick black bar: a summary task
    - a lighter horizontal bar: durations of tasks
    - an arrow: dependencies between tasks
- Symbols of **Tracking Gantt Charts**
    - a black horizontal bar: actual dates.
    - a lighter horizontal bar: planned dates.
    - a hollow(空心) diamond(◇): a slipped milestone

### 7. Critical Path Method(CPM)

- **CPM** is a network diagramming technique used to predict total project duration. A **critical path** for a project is the series of activities that determines the **earliest** time by which the project can be. completed.
- **Slack(鬆弛)** or **float** is the amount of time an activity may be delayed without delaying a succeeding activity or the project finish date.
- **forward pass**: determines early start and finish dates.
- **backward pass**: determines late start and finish dates.

<img src="./cpm.png">


<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
