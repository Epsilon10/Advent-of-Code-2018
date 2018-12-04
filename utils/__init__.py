from functools import wraps
import time

def timed(f):
    """
    Simple utility decorator which prints out 
    the execution time of the wrapped function.
    """
    @wraps(f)
    def wrapper(*args, **kwargs):
        start = time.monotonic()
        result = f(*args, **kwargs)
        end = time.monotonic()
        print(f'{f.__name__} - time taken: {end-start:.5f} seconds')
        return result
    return wrapper