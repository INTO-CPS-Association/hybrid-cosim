'''
Created on Mar 5, 2016

@author: claudio gomes
'''

class Utils(object):
    
    @staticmethod
    def copyMapToStateTrace(target, current_step, current_iteration, source):
        for var in source:
            assert target.has_key(var)
            if current_iteration==0:
                assert current_step == len(target[var])
                target[var].append([source[var]])
            else:
                assert current_step == len(target[var])-1
                assert current_iteration == len(target[var][current_step])
                target[var][current_step].append(source[var])
    
    @staticmethod
    def trimList(listToTrim, target_size):
        assert target_size <= len(listToTrim)
        assert target_size >= 0
        while target_size < len(listToTrim):
            del listToTrim[-1]
        assert target_size == len(listToTrim)