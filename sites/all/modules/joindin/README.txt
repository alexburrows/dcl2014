Welcome to the joindin-drupal wiki!

This repository will contain a drupal module to interface a Drupal site with the
joind.in website.

For what do we need this?

From joind.in's about page:

Joind.in is the replacement for all those paper submission forms that get left
on the floor at the end of an event. The site gives details of events past,
present and future, the sessions, timetable and speakers at each, and allows
all attendees to register and leave feedback - for the sessions and for the
event itself.

But we can do all this in Drupal. There's even a Conference Organising
Distribution that will do this. For what do we need this?

1) Data in Joind.in is persistent. I've been to Drupal events and found that six
months later when I've wanted to remind myself what talks were given, who gave a
particular talk, or see the feedback that the site itself has been torn down.
On Joind.in, I can see all data for listed events going back to 2008. I can find
every talk I've ever seen at a PHP conference at Joind.in.

2) Because Joind.in stores data on many many events, it is possible to track
speaker profiles across multiple talks and events, giving attendees a better
insight into those presenting at your event, allowing them to make a more
informed choice and increasing the profile of your speakers.

3) This doesn't have to be an either/or decision. Joind.in has a
comprehensive API http://joind.in/api which supports writing data back to it.
So either the Drupal site or Joind.in could be the master of the data. (writes
in both directions could get messy). Reflecting the data on both sites means
that should one site be unavailable the information is still "out there". But
you get to have your data on your snazzy (do people still use that word?) Drupal
site, but aggregated with all the other content hosted on joind.in.

My primary aim is to produce a module that will support data replication between
a Drupal site and Joind.in for potentially multiple talks. It will provide
entities to represents the data elements provided by the joind.in API, such as
events and speakers. It will not mandate that you use them, and provide the
functionality to designate existing entity types as representing joind.in data
elements so that as little as possible of your Drupal site's architecture is
determined by your decision to use this module. This will make it easy to add
the module to existing sites that already contain content types for talks (for
example).

The module will initially be written for Drupal 7. There is no current intention
to backport to Drupal 6.

The long term aim is that the joind.in module will become part of COD. But it
will be easier to have that discussion with the relevant people when the module
is written and proved.
