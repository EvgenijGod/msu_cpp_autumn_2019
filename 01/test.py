import subprocess

def check(expr, result):
    out = subprocess.run(['./my_prog', expr], stdout = subprocess.PIPE, stderr = subprocess.STDOUT)
    if len(out.stdout) == 0:
        out.stdout = out.stderr
    if out.stdout.decode('utf-8') != result + '\n':
        print('error "{0}" != {1}, got {2}'.format(expr, result, out.stdout.decode('utf-8')))
    else:
        print('"{0}" == {1}, OK\n'.format(expr, result))

check('-2147483648 + 1', '-2147483647')
check('1 + 3* 4', '13')
check('1 - - 3 + - - - 70', '-66')
check('1 * 2 + 1 * 2 --1 * -2 + 0', '2')
check('1 + --3 * ---4 * 1 + -0 + --0', '-11')
check('4 / 3 * 9', '9')
check('2 +  ', 'ERROR : NUMBER IS LOST')
check(' +  ', 'ERROR : NUMBER IS LOST')
check('2 / 0 + 777', 'ERROR : ZERO DIVISION')
check('4 4', 'ERROR : SIGN IS LOST')
check('', 'ERROR : NUMBER IS LOST')
check('1 + 10 / 0 * 3 + 1 * 0 + ---1', 'ERROR : ZERO DIVISION')
check('4 * +4', 'ERROR : NUMBER IS LOST')
check("4 * 4 +", 'ERROR : NUMBER IS LOST')

