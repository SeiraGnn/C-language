TITLE: Recover

USAGE: ./recover card.raw

The application of this project is, for me, is one the coolest one I've done. Firstly, because it changed the way I look at and think of memory storage, and secondly because it lets you roleplay as a computer forensics expert solving a crime case. Okay, in reality there's no crime in the design and instructions of the project, but it's still really cool and you'll see why I felt that way.

The instructor handed us a copy or image file from a phone's memory card. That card had previously stored some pictures of Harvard's campus that had been recently taken by the instructor; however, he had deleted them BEFORE making the copy/image. Our task was to read into the card's memory and retrieve the pictures! If you're like me before having taken this course, you might be wondering how on Earth someone can possibly retrieve a file that's been deleted without even accessing the operating system that handled it.

As it turns out, in the computer world, “deleted” tends not to mean “deleted” so much as “forgotten.” The information is still there, the only thing that's changed is that the computer no longer cares about where it is nor does it reserve that space not to be overwritten. But then, how could one identify which bytes represent a picture and which don't?  

Thanks to file formats, we know that the first three bytes must be 0xff, 0xd8 and 0xff. So one can read through the data and look for this 'signatures' or patterns.

We can also take advantage of the fact that digital cameras often initialize cards with a FAT file system whose “block size” is 512 bytes (B). The implication is that these cameras only write to those cards in units of 512 B. A photo that's 1 MB (i.e., 1,048,576 B) thus takes up 1048576 ÷ 512 = 2048 “blocks” on a memory card. But so does a photo that's, say, one byte smaller (i.e., 1,048,575 B)! The wasted space on disk is called “slack space.” Forensic investigators often look at slack space for remnants of suspicious data (and now you see how one can feel as a crime-busting hacker while working on this.)

