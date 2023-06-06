import pyhpx
def no(a):
    return a
s = pyhpx.new_async(no,2)
print("hello1")
try:
    print(s.get())
    print("hello")
except Exception as e:
    print(e)


def fibonacci(n):
    # pdb.set_trace()
    if(n<2):
        return n
    
    n1 = pyhpx.new_async(fibonacci,n - 1)
    n2 = pyhpx.new_async(fibonacci,n - 2)

    if n1.is_ready() and n2.is_ready():
        print("hello")
        return n1.get() + n2.get()

# print(fibonacci(10))
