OpenACC/CUDA training for beginners
===================================





.. prereq::

   Before attending this workshop, please make sure that you have
   access to an HPC cluster with Nvidia GPUs and the PGI compiler.
   Alternatively, you can use a cloud service like Google Colab which
   offers access to GPUs in the cloud. See the :ref:`setup` section
   for further details.


.. toctree::
   :maxdepth: 1
   :caption: Table of contents

   1.01_gpu-introduction
   1.02_openacc-introduction
   1.03_openacc-heat-equation
   2.01_cuda-introduction
   2.02_cuda-heat-equation


.. toctree::
   :maxdepth: 1
   :caption: Reference

   setup
   quick-reference
   guide



.. _learner-personas:

Who is the course for?
----------------------

This course is for students, researchers, engineers and programmers
who would like to quickly get started with GPU programming using
OpenACC and/or CUDA.  Some previous experience with C/C++ or Fortran
is required, and the lesson furthermore assumes that participants have
some familiarity with the following topics:

- Logging in to supercomputers and using a bash terminal
- Compiling C/C++ or Fortran codes using compilers and makefiles
  
Tentative schedule
------------------

.. list-table::
   :widths: 25 50
   :header-rows: 1

   * - Day 1
     -
   * - 9:00 -  9:10
     - Introduction to ENCCS
   * - 9:10 -  9:40 
     - Introduction to accelerators
   * - 9:40 -  9:50
     - Break
   * - 9:50 - 10:20
     - Introduction to OpenACC
   * - 10:20 - 10:30
     - Break-out rooms
   * - 10:30 - 10:40
     - Break
   * - 10:40 - 11:10
     - Introduction to OpenACC (cont.)
   * - 11:10 - 11:40
     - Break-out rooms
   * - 11:40 - 12:00
     - Wrap-up of day 1

.. list-table::
   :widths: 25 50
   :header-rows: 1

   * - Day 2
     -
   * - 9:00 -  9:10
     - Follow-ups from day 1
   * - 9:10 -  9:50
     - Introduction to CUDA
   * - 9:50 - 10:00
     - Break-out rooms
   * - 10:00 - 10:10
     - Break
   * - 10:10 - 10:35
     - Real-life example
   * - 10:35 - 10:50
     - Break-out rooms
   * - 10:50 - 11:00
     - Break
   * - 11:00 - 11:30
     - Improve the code
   * - 11:30 - 11:50
     - Break-out rooms
   * - 11:50 - 12:00
     - Wrap-up







About the course
----------------

This lesson is an introduction to GPU programming using the
directive-based OpenACC paradigm and language-extension-based
CUDA. The course consists of lectures, type-along and hands-on
exercises. Topics covered include the architecture of the GPU
accelerators, basic usage of OpenACC and CUDA, and how to control data
movement between CPUs and GPUs. Basic optimization of the code will
also be covered. 

After the course the participants should have the basic skills needed
for utilising OpenACC or CUDA with new or existing programs.

The participants are assumed to have knowledge of Fortran and/or C
programming languages. Since participants will be using HPC clusters
to run the examples, fluent operation in a Linux/Unix environment is
assumed.

See also
--------

There are many excellent resources online for learning OpenACC and CUDA.
To name only few:

- Official `OpenACC site <https://www.openacc.org/>`_
- `Nvidia Deep Learning institute <https://www.nvidia.com/en-us/training/>`_ 
- `CSC training resources on OpenACC <https://github.com/csc-training/openacc/>`_

Credits
-------

The lesson file structure and browsing layout is inspired by and derived from
`work <https://github.com/coderefinery/sphinx-lesson>`_ by `CodeRefinery
<https://coderefinery.org/>`_ licensed under the `MIT license
<http://opensource.org/licenses/mit-license.html>`_. We have copied and adapted
most of their license text.

Several examples and exercises in this lesson have been adapted from the following
sources:

- `GPUBootcamp Official Training Materials <https://github.com/gpuhackathons-org/gpubootcamp>`_
- `CSC OpenACC training material <https://github.com/csc-training/openacc>`_

Instructional Material
^^^^^^^^^^^^^^^^^^^^^^

This lesson material has been developed by Artem Zhmurov (ENCCS, PDC),
Jing Gong (ENCCS) and others at `ENCCS <https://enccs.se/>`_.

All ENCCS instructional material is made available under the `Creative Commons
Attribution license (CC-BY-4.0)
<https://creativecommons.org/licenses/by/4.0/>`_. The following is a
human-readable summary of (and not a substitute for) the `full legal text of the
CC-BY-4.0 license <https://creativecommons.org/licenses/by/4.0/legalcode>`_.
You are free:

- to **share** - copy and redistribute the material in any medium or format
- to **adapt** - remix, transform, and build upon the material for any purpose,
  even commercially.

The licensor cannot revoke these freedoms as long as you follow these license terms:

- **Attribution** - You must give appropriate credit (mentioning that your work
  is derived from work that is Copyright (c) ENCCS and, where practical, linking
  to `<https://enccs.se>`_), provide a `link to the license
  <https://creativecommons.org/licenses/by/4.0/>`_, and indicate if changes were
  made. You may do so in any reasonable manner, but not in any way that suggests
  the licensor endorses you or your use.
- **No additional restrictions** - You may not apply legal terms or
  technological measures that legally restrict others from doing anything the
  license permits. With the understanding that:

  - You do not have to comply with the license for elements of the material in
    the public domain or where your use is permitted by an applicable exception
    or limitation.
  - No warranties are given. The license may not give you all of the permissions
    necessary for your intended use. For example, other rights such as
    publicity, privacy, or moral rights may limit how you use the material.
  
Software
^^^^^^^^

Except where otherwise noted, the example programs and other software provided
by ENCCS are made available under the `OSI <http://opensource.org/>`_-approved
`MIT license <http://opensource.org/licenses/mit-license.html>`_.

