.global reset

reset:

           ldr SP, =Stack_top
           bl main
	     stop: b stop