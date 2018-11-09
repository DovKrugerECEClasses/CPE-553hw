Solar System
The solarsystem.dat file contains data on a number of planets and moons.  For the purposes of the simulation you can consider them all the same. You need to give each a realistic initial velocity.  From that point on, you must compute the motion of the bodies using the universal Gravitational Law (Newton).

F = Gm1m2 / (r12^2)

Each body will need to store its location, so that the distance between any two bodies is the distance between the points.  You can track collisions, if any two bodies touch you can call a function that will decide what to do, but this is not a normal occurrence.

Quiz
To build a better assessment engine for Stevens courses, we need an engine that can read in a file of questions and generate a visual as follows:

1. Multiple choice questions, with a text question and a number of text choices.
2. 


School Scheduler

Stevens needs a new schedule for courses.  We have undergraduates,
masters and PhD students.  We have professors who teach classes.  Some
are full time, and some are adjuncts who just come in to teach one or
two classes.

Classes are taught in classrooms.  The rooms must be capable of holding all the people who are supposed to be there.  So classes must not be scheduled in rooms insufficient to handle the number of people.

We need to make sure that no person is scheduled to be in the same
place at the same time.  We also need to make sure that two or more
classes are not scheduled to be in the same classrooom at the same
time.

In addition, we need sufficient time between classes for students to
get from one place to another.


