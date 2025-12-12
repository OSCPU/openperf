-- https://www.tutorialspoint.com/lua/lua_quick_sort.htm

print("Quick Sort")

function check (a, f)
  f = f or function (x,y) return x<y end;
  for n = #a, 2, -1 do
    assert(not f(a[n], a[n-1]))
  end
end

-- function to create a partition
function partition(list, low, high)
   -- last element is a pivot
   local pivot = list[high]
   local i = low - 1 -- index of first element

   -- loop on elements of the partition
   for j = low, high - 1 do
      -- swap number if lower than pivot
      if list[j] <= pivot then
         i = i + 1
         list[i], list[j] = list[j], list[i]
      end
   end

   -- Swap list[i + 1] with list[high]
   list[i + 1], list[high] = list[high], list[i + 1]
   return i + 1  -- return the index to partition
end

function quick_sort(list, low, high)
   if low < high then
      -- Partition the list and get the partitioning index
      local pi = partition(list, low, high)

      -- Recursively quick sort elements before and after partition
      quick_sort(list, low, pi - 1)
      quick_sort(list, pi + 1, high)
   end
   return list
end

-- Example usage:
local numbers = {}
local len = 50000000
for i = 0, len do
  numbers[i] = math.random(10000000)
end

local sorted_numbers = quick_sort(numbers, 1, #numbers)
check(sorted_numbers)
print("OK")
