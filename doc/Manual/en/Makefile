POD2HTML = pod2html
POD2MAN = pod2man

HTMLS = BH_Algo.html \
	BH_Args.html \
	BH_Bitmap.html \
	BH_Box2f.html \
	BH_Box3f.html \
	BH_Color.html \
	BH_Hashmap.html \
	BH_IO.html \
	BH_Line.html \
	BH_Mat3f.html \
	BH_Mat4f.html \
	BH_Math.html \
	BH_Plane.html \
	BH_Quat.html \
	BH_Queue.html \
	BH_Ray2f.html \
	BH_Ray3f.html \
	BH_String.html \
	BH_Thread.html \
	BH_Unicode.html \
	BH_Util.html \
	BH_Vec2f.html \
	BH_Vec2i.html \
	BH_Vec3f.html \
	BH_Vec3i.html \
	BH_Vec4f.html \
	BH_Vec4i.html

MANS = BH_Algo.3 \
	BH_Args.3 \
	BH_Bitmap.3 \
	BH_Box2f.3 \
	BH_Box3f.3 \
	BH_Color.3 \
	BH_Hashmap.3 \
	BH_IO.3 \
	BH_Line.3 \
	BH_Mat3f.3 \
	BH_Mat4f.3 \
	BH_Math.3 \
	BH_Plane.3 \
	BH_Quat.3 \
	BH_Queue.3 \
	BH_Ray2f.3 \
	BH_Ray3f.3 \
	BH_String.3 \
	BH_Thread.3 \
	BH_Unicode.3 \
	BH_Util.3 \
	BH_Vec2f.3 \
	BH_Vec2i.3 \
	BH_Vec3f.3 \
	BH_Vec3i.3 \
	BH_Vec4f.3 \
	BH_Vec4i.3

all: $(MANS) $(HTMLS)

%.3: %.pod
	$(POD2MAN) -c "BHLib" -s 3 -r "0.1.0" $< $@

%.html: %.pod
	$(POD2HTML) --css ../style.css --htmlroot=. --podpath=. $< --outfile $@

dist: $(MANS) $(HTMLS)
	zip html.zip $(HTMLS)
	zip man.zip $(MANS)

clean:
	-rm -f $(MANS) $(HTMLS) pod2htmd.tmp man.zip html.zip

