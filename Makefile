
# CFLAGS += -Wall -Werror

  Obj   = Obj
  Objs  = $(patsubst %.cpp, $(Obj)/%.o, $(Srcs))
  Srcs  = $(shell echo *cpp)
  Targ  = rckt

$(Obj)/%.o : %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $^

# --------------------------------------------------------------------
all : $(Targ).xgr

$(Targ).xgr : $(Targ).txt $(Targ).k
	$(Targ).k $(Targ).txt > $@

$(Targ).txt : $(Targ)
	$(Targ) $(Targ).cmd | tee $@

$(Targ) : $(Obj) $(Objs)
	$(CXX) -o $(Targ) $(Objs) $(LIBS)

$(Obj) :
	mkdir $@

# --------------------------------------------------------------------
check :
	@ echo Src: $(Srcs)
	@ echo Obj: $(Objs)

neat :
	rm -f *~ *stackdump

clean : neat
	rm -rf $(Obj) *.exe *.txt *.xgr
