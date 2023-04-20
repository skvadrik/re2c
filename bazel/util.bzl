visibility("public")

def sed_args(*args):
    return "{" + ";".join(args) + ";}"
