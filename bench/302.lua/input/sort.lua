print("sort test for table")

function check (a, f)
  f = f or function (x,y) return x<y end;
  for n = #a, 2, -1 do
    assert(not f(a[n], a[n-1]))
  end
end

a = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
     "Oct", "Nov", "Dec"}

table.sort(a)
check(a)

A = {"醠o", "\0first :-)", "alo", "then this one", "45", "and a new"}
table.sort(A)
check(A)

table.sort(A, function (x, y)
          load(string.format("A[%q] = ''", x), "")()
          collectgarbage()
          return x<y
        end)


tt = {__lt = function (a,b) return a.val < b.val end}
a = {}
for i=1,10 do  a[i] = {val=math.random(100)}; setmetatable(a[i], tt); end
table.sort(a)
check(a, tt.__lt)
check(a)

print"OK"
