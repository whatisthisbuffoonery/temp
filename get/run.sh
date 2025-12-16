# list files
ls -la /home/dthoo/temp/get
ls -la /home/dthoo/temp/get/ohno

# print all .c/.h so I can inspect them
for f in /home/dthoo/temp/get/*.[ch] /home/dthoo/temp/get/ohno/*.[ch]; do
  [ -e "$f" ] || continue
  printf '\n==== %s ====\n' "$f"
  sed -n '1,240p' "$f"
done
