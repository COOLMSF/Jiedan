import r2pipe

class GetBianryInfo:
    binary_name = None
    r2 = None
    
    def __init__(self, binary_name) -> None:
        binary_name = binary_name
        self.r2 = r2pipe.open(binary_name)
        self.r2.cmd('aaa')
        
        
    def get_function(self):
        return self.r2.cmd('afl')
    
    def get_import(self):
        return self.r2.cmd('ii')
    
    def get_export(self):
        return self.r2.cmd('iE')
    
    def get_string(self):
        return self.r2.cmd('iz')
    
    def get_sessions(self):
        return self.r2.cmd('iS')
    